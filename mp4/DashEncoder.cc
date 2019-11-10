#include "DashEncoder.h"

#include <cstring>
#include <fstream>
#include <iomanip>
#include <sstream>

#include "ArrayByteSource.h"
#include "AVCSampleEntry.h"
#include "ChunkOffset.h"
#include "DataEntryURL.h"
#include "DataReference.h"
#include "FileType.h"
#include "HandlerReference.h"
#include "MovieFragmentHeader.h"
#include "MediaHeader.h"
#include "MovieData.h"
#include "MovieHeader.h"
#include "MP4Exception.h"
#include "NALU.h"
#include "SampleDescription.h"
#include "SampleToChunk.h"
#include "SampleSize.h"
#include "SegmentType.h"
#include "SPS.h"
#include "StreamByteSink.h"
#include "SyncSample.h"
#include "TimeToSample.h"
#include "TrackFragmentDecodeTime.h"
#include "TrackFragmentHeader.h"
#include "TrackFragmentRun.h"
#include "TrackHeader.h"
#include "TrackExtends.h"
#include "VideoMediaHeader.h"
   
/************************************************************************//**
*
****************************************************************************/ 
DashEncoder::DashEncoder() 
           : init("init") {
               
    fragment_count = 1;
    fragment = NULL;
    
} // end of constructor
   
/************************************************************************//**
*
****************************************************************************/ 
void DashEncoder::addNALU(uint8_t* data, int size) {
    
    if(size<=0) return;
    
    /**************************************
    * skip the start code if there is one *
    **************************************/
    if(size>4 && data[0] == 0 && data[1] == 0 && data[2] == 0 && data[3] == 1) {
        data += 4;
    } else if(size>3 && data[0] == 0 && data[1] == 0 && data[2] == 1) {
        data += 3;
    }

    /********************
    * get the NALU type *
    ********************/
    int type = data[0] & ((1<<5)-1);
    
    //std::cout << "type = "<<type<<std::endl;
    
    if(type == 7) {
        /******
        * SPS *
        ******/
        ArrayByteSource array(data, size);
        NALU nalu;
        nalu.read(array);
        SPS* sps = dynamic_cast<SPS*>(nalu.getContents());
        if(sps == NULL) {
            throw MP4Exception("Could not parse SPS");
        }
        
        createInit(sps->getWidth(), sps->getHeight());
        AVCConfiguration* config = getAVCConfiguration();
        if(config == NULL) {
            throw MP4Exception("no AVC config");
        }
        config->addSPS(data, size);
        
    } else if(type == 8) {
        /******
        * PPS *
        ******/
        AVCConfiguration* config = getAVCConfiguration();
        if(config == NULL) {
            throw MP4Exception("no AVC config");
        }
        config->addPPS(data, size);
        
    } else if(type == 5) {
        /**********
        * I frame *
        **********/
        createFragment();
        addFrame(data, size);
        
        
    } else if(type == 1) {
        /**********
        * P frame *
        **********/
        addFrame(data, size);
        
        
    } else {
        /**********
        * whaaaa? *
        **********/
        throw MP4Exception("Unsupported NALU type ");
        
    }
        
    
} // end of addNALU method
   
/************************************************************************//**
*
****************************************************************************/ 
void DashEncoder::createInit(uint32_t width, uint32_t height) {
    
    init.clear();
    
    FileType* ftyp = new FileType();
    ftyp->set("dash", 0);
    ftyp->add("iso6");
    ftyp->add("avc1");
    ftyp->add("mp41");
    
    Box* box = new Box();
    box->setContents(ftyp);
    init.add(box);
    
    Container* moov = new Container("moov");
    MovieHeader* mvhd = new MovieHeader();
    moov->add(mvhd);
    
    Container* mvex = new Container("mvex");
    moov->add(mvex);
    
    TrackExtends* trex = new TrackExtends();
    mvex->add(trex);
    
    Container* trak = new Container("trak");
    moov->add(trak);
    
    TrackHeader* tkhd = new TrackHeader();
    trak->add(tkhd);
    
    Container* mdia = new Container("mdia");
    trak->add(mdia);
    
    MediaHeader* mdhd = new MediaHeader();
    mdia->add(mdhd);
    
    HandlerReference* hdlr = new HandlerReference();
    mdia->add(hdlr);
    
    Container* minf = new Container("minf"); // Media Information
    mdia->add(minf);
    
    Container* dinf = new Container("dinf"); // Data Information
    minf->add(dinf);
    
    DataReference* dref = new DataReference();
    dinf->add(dref);
    
    DataEntryURL* url = new DataEntryURL();
    dref->add(url);
    
    Container* stbl = new Container("stbl");
    minf->add(stbl);
    
    SampleDescription* stsd = new SampleDescription();
    stbl->add(stsd);
    
    AVCSampleEntry* avc1 = new AVCSampleEntry();
    avc1->setDimensions(width, height);
    avc1->setConfig(new AVCConfiguration());
    stsd->add(avc1);
    
    TimeToSample* stts = new TimeToSample();
    stbl->add(stts);
    
    SampleToChunk* stsc = new SampleToChunk();
    stbl->add(stsc);
    
    ChunkOffset* stco = new ChunkOffset();
    stbl->add(stco);
    
    SampleSize* stsz = new SampleSize();
    stbl->add(stsz);
    
    SyncSample* stss = new SyncSample();
    stbl->add(stss);
    
    VideoMediaHeader* vmhd = new VideoMediaHeader();
    minf->add(vmhd);

    box = new Box();
    box->setContents(moov);
    init.add(box);
    
} // end of createInit method
   
/************************************************************************//**
*
****************************************************************************/ 
void DashEncoder::createFragment() {
    
    if(fragment_count==1) {
        /*****************************
        * spit out the init fragment *
        *****************************/
        StreamByteSink sink(new std::ofstream("dash/init.mp4"));
        init.write(sink);
        
        
    } else {
        /*********************************
        * spit out the previous fragment *
        *********************************/
        writeFragment();
        
    }
    
    std::cout << "fragment "<<fragment_count<<std::endl;
    
    fragment = new Container("    ");
    
    SegmentType* styp = new SegmentType();
    styp->set("dash", 0);
    styp->add("iso6");
    styp->add("avc1");
    styp->add("mp41");
    
    Box* box = new Box();
    box->setContents(styp);
    fragment->add(box);
    
    Container* moof = new Container("moof");
    
    MovieFragmentHeader* mfhd = new MovieFragmentHeader();
    mfhd->setSequenceNumber(fragment_count++);
    moof->add(mfhd);
    
    Container* traf = new Container("traf");
    moof->add(traf);
    
    TrackFragmentHeader* tfhd = new TrackFragmentHeader();
    tfhd->setSampleDescriptionIndex(0);
    tfhd->setDefaultSampleDuration(0);
    traf->add(tfhd);
    
    // tfdt Track Fragment Decode Time
    TrackFragmentDecodeTime* tfdt = new TrackFragmentDecodeTime();
    tfdt->setBaseMediaDecodeTime(0);
    traf->add(tfdt);
    
    TrackFragmentRun* trun = new TrackFragmentRun();
    traf->add(trun);
    
    MovieData* mdat = new MovieData();
    fragment->add(mdat);
    
    box = new Box();
    box->setContents(moof);
    fragment->add(box);
    
} // end of createChunk method
      
/************************************************************************//**
*
****************************************************************************/
void DashEncoder::writeFragment() {
    
    std::ostringstream name;
    name <<"dash/fragment"
            <<std::setw(6)<<std::setfill('0')<<(fragment_count-1)
            <<".mp4";
            
    StreamByteSink sink(new std::ofstream(name.str().c_str()));
    fragment->write(sink);
        
} // end of writeFragment method

/************************************************************************//**
*
****************************************************************************/ 
void DashEncoder::addFrame(uint8_t* data, int size) {
    
    /*********************
    * get the type again *
    *********************/
    int type = data[0] & ((1<<5)-1);
    
    TrackFragmentRun* trun = 
                          dynamic_cast<TrackFragmentRun*>(fragment->get("trun"));
    trun->add();
    trun->setSampleSize(size+4); // 4 byte size field
    
    if(type == 5) trun->setSampleFlags(0);
    else          trun->setSampleFlags(0x10000);
    
    DataChunk* chunk = new DataChunk();
    chunk->setSize(size);
    memcpy(chunk->getData(), data, size);
    
    MovieData* mdat = dynamic_cast<MovieData*>(fragment->get("mdat"));
    mdat->add(chunk);
    
    
} // end of addFrame method
   
/************************************************************************//**
*
****************************************************************************/ 
AVCConfiguration* DashEncoder::getAVCConfiguration() {
    
    SampleDescription* stsd = dynamic_cast<SampleDescription*>(init.get("stsd"));
    if(stsd == NULL) return NULL;
    
    AVCSampleEntry* avc1 = dynamic_cast<AVCSampleEntry*>(stsd->get("avc1"));
    return dynamic_cast<AVCConfiguration*>(avc1->getConfig());

    
} // end of getAVCConfiguration method
