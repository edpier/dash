#include "Box.h"

#include <iostream>

#include "AVCConfiguration.h"
#include "AVCSampleEntry.h"
#include "BitRate.h"
#include "ChunkOffset.h"
#include "Container.h"
#include "DataEntryURL.h"
#include "DataReference.h"
#include "EditList.h"
#include "EventMessage.h"
#include "FileType.h"
#include "HandlerReference.h"
#include "InitialObjectDescriptor.h"
#include "ItemList.h"
#include "MediaHeader.h"
#include "Meta.h"
#include "MovieFragmentHeader.h"
#include "MovieHeader.h"
#include "MP4Exception.h"
#include "SampleDescription.h"
#include "SampleSize.h"
#include "SampleToChunk.h"
#include "SegmentType.h"
#include "SkipContents.h"
#include "SoundMediaHeader.h"
#include "SubByteSource.h"
#include "SyncSample.h"
#include "TimeToSample.h"
#include "TrackExtends.h"
#include "TrackFragmentDecodeTime.h"
#include "TrackFragmentHeader.h"
#include "TrackFragmentRun.h"
#include "TrackHeader.h"
#include "VideoMediaHeader.h"


/**************************************************************************//**
*
******************************************************************************/
Box::Box() {
    
    contents = NULL;
    
} // end of constructor

/**************************************************************************//**
* @details This class takes ownership of the contents
******************************************************************************/
Box::Box(Contents* contents) {
    
    this->contents = contents;
    
} // end of constructor with contents

/**************************************************************************//**
*
******************************************************************************/
Box::~Box() {
    
    delete contents;
    
} // end of destructor

/**************************************************************************//**
*
******************************************************************************/
void Box::setContents(Contents* contents) {
    
    if(this->contents != NULL) delete this->contents;
    this->contents = contents;
    
} // end of setContents method

/**************************************************************************//**
*
******************************************************************************/Contents* Box::getContents() { return contents; }
    
/**************************************************************************//**
*
******************************************************************************/
const Contents* Box::getContents() const { return contents; }

/**************************************************************************//**
*
******************************************************************************/
uint64_t Box::getSize() const {
    
    if(contents == NULL) {
        throw MP4Exception("Empty box");
    }
    
    Size size = contents->getSize();
    size.addHeader();
    
    return size;
    
} // end of getSize method

/**************************************************************************//**
*
******************************************************************************/
void Box::read(ByteSource& source) {
    
    /********************************
    * read the size and type fields *
    ********************************/
    Size size;
    Type type;
    
    size.read(source);
    type.read(source);
    std::cout <<std::endl << "type: "<<type<<" size="<<size<<std::endl;
    
    /******************************************
    * read the contents according to the size *
    ******************************************/
    const std::string& type_string = type.getString();
    Contents* contents = NULL;
    
    if(type_string == "moov" ||
       type_string == "mdia" ||
       type_string == "minf" ||
       type_string == "dinf" ||
       type_string == "stbl" ||
       type_string == "udta" ||
       type_string == "edts" ||
       type_string == "mvex" ||
       type_string == "moof" ||
       type_string == "traf" ||
       type_string == "trak"   ) {
        /************
        * container *
        ************/
        contents = new Container(type);
        
    } else if(type_string == "mp4a" ||
              type_string == "mdat" ||
              type_string == "free" ||
              type_string == "skip"   ) {
        /*******
        * skip *
        *******/
        contents = new SkipContents(type, size);
    }
    
    else if(type_string == "ftyp") contents = new FileType();
    else if(type_string == "mvhd") contents = new MovieHeader();
    else if(type_string == "tkhd") contents = new TrackHeader();
    else if(type_string == "mdhd") contents = new MediaHeader();
    else if(type_string == "hdlr") contents = new HandlerReference();
    else if(type_string == "smhd") contents = new SoundMediaHeader();
    else if(type_string == "dref") contents = new DataReference();
    else if(type_string == "url ") contents = new DataEntryURL();
    else if(type_string == "stsd") contents = new SampleDescription();
    else if(type_string == "stsc") contents = new SampleToChunk();
    else if(type_string == "stsz") contents = new SampleSize();
    else if(type_string == "stco") contents = new ChunkOffset();
    else if(type_string == "vmhd") contents = new VideoMediaHeader();
    else if(type_string == "stss") contents = new SyncSample();
    else if(type_string == "stts") contents = new TimeToSample();
    else if(type_string == "meta") contents = new Meta();
    else if(type_string == "elst") contents = new EditList(size);
    else if(type_string == "trex") contents = new TrackExtends();
    else if(type_string == "mfhd") contents = new MovieFragmentHeader();
    else if(type_string == "tfhd") contents = new TrackFragmentHeader();
    else if(type_string == "trun") contents = new TrackFragmentRun();
    else if(type_string == "emsg") contents = new EventMessage();
    else if(type_string == "tfdt") contents = new TrackFragmentDecodeTime();
    else if(type_string == "styp") contents = new SegmentType();
    else if(type_string == "ilst") contents = new ItemList();
    else if(type_string == "avc1") contents = new AVCSampleEntry();
    else if(type_string == "avcC") contents = new AVCConfiguration();
    else if(type_string == "btrt") contents = new BitRate();
    else if(type_string == "iods") contents = new InitialObjectDescriptor();
    else {
        throw MP4Exception("unsupported type ");
    }

    uint64_t remaining = size - size.getSize() - Type::getSize();
    SubByteSource sub(type.getString(), source, remaining);
    contents->read(sub);
    
    if(sub.getRemaining() != 0) {
        throw MP4Exception(std::string("Leftover bytes in ")+type.getString()+std::string(" box"));
    }
    
    setContents(contents);
    
} // end of read method

/**************************************************************************//**
*
******************************************************************************/
void Box::write(ByteSink& sink) const {
    
    if(contents == NULL) {
        throw MP4Exception("Empty box");
    }
    
    Size size = contents->getSize();
    size.addHeader();
    size.write(sink);
    contents->getType().write(sink);
    
    contents->write(sink);

} // end of write method
