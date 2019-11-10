#include <fstream>

#include "Box.h"
#include "ChunkOffset.h"
#include "Container.h"
#include "DataEntryURL.h"
#include "DataReference.h"
#include "FileType.h"
#include "HandlerReference.h"
#include "MediaHeader.h"
#include "MovieFragmentHeader.h"
#include "MovieHeader.h"
#include "SampleDescription.h"
#include "SampleSize.h"
#include "SampleToChunk.h"
#include "SegmentType.h"
#include "StreamByteSink.h"
#include "SyncSample.h"
#include "TimeToSample.h"
#include "TrackExtends.h"
#include "TrackFragmentDecodeTime.h"
#include "TrackFragmentHeader.h"
#include "TrackFragmentRun.h"
#include "TrackHeader.h"
#include "VideoMediaHeader.h"

int main(int argc, char** argv) {
    
    StreamByteSink sink(new std::ofstream("out2.mp4"));
    
    Box box;
    
    SegmentType* styp = new SegmentType();
    styp->set("dash", 0);
    styp->add("iso6");
    styp->add("avc1");
    styp->add("mp41");
    
    box.setContents(styp);
    box.write(sink);
    
    Container* moof = new Container("moof");
    
    MovieFragmentHeader* mfhd = new MovieFragmentHeader();
    mfhd->setSequenceNumber(1);
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
    // need to set things
    // set nalu size and flags to indicate I frame or not.
    // sample size includes the four byte size field
    
    box.setContents(moof);
    box.write(sink);
    

    
} //end of main
