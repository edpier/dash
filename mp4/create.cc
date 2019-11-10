#include <fstream>

#include "AVCSampleEntry.h"
#include "Box.h"
#include "ChunkOffset.h"
#include "Container.h"
#include "DataEntryURL.h"
#include "DataReference.h"
#include "FileType.h"
#include "HandlerReference.h"
#include "MediaHeader.h"
#include "MovieHeader.h"
#include "SampleDescription.h"
#include "SampleSize.h"
#include "SampleToChunk.h"
#include "StreamByteSink.h"
#include "SyncSample.h"
#include "TimeToSample.h"
#include "TrackExtends.h"
#include "TrackHeader.h"
#include "VideoMediaHeader.h"

int main(int argc, char** argv) {
    
    StreamByteSink sink(new std::ofstream("out.mp4"));
    
    Box box;
    
    FileType* ftyp = new FileType();
    ftyp->set("dash", 0);
    ftyp->add("iso6");
    ftyp->add("avc1");
    ftyp->add("mp41");
    
    box.setContents(ftyp);
    box.write(sink);
    
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
    avc1->setDimensions(1080, 720);
    stsd->add(avc1);
    
    // need to add an avc1 box to stsd
    
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
    
    // what's an emsg? It's a YouTube add.
    
    
    
    box.setContents(moov);
    box.write(sink);
    

    
} //end of main
