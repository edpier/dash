#include <fstream>

#include "ArrayByteSource.h"
#include "AVCConfiguration.h"
#include "AVCSampleEntry.h"
#include "Box.h"
#include "Container.h"
#include "NALU.h"
#include "SampleDescription.h"
#include "SkipContents.h"
#include "StreamByteSource.h"
#include "SubByteSource.h"

int main(int argc, char** argv) {
    
     //StreamByteSource source(new std::ifstream("/home/epier/git/vipa/test/FA-18_carrier_take-off.mp4"));
    
    //StreamByteSource source(new std::ifstream("/home/epier/git/dash/out.mp4"));
     
    //StreamByteSource source(new std::ifstream("../z3_init.mp4"));
    //StreamByteSource source(new std::ifstream("../z3_seg1.mp4"));
    //StreamByteSource source(new std::ifstream("../z3_seg2.mp4"));
    
    //StreamByteSource source(new std::ifstream("dash/init.mp4"));
    //StreamByteSource source(new std::ifstream("dash/fragment000001.mp4"));
    //StreamByteSource source(new std::ifstream("/home/epier/pubvipa/out3.mp4"));
    StreamByteSource source(new std::ifstream("/home/epier/git/vipa/out3.mp4"));
    
    Container all("    ");
    while(source.getRemaining()>0) {
        Box* box = new Box();
        box->read(source);
        all.add(box);
    }
    
//     SampleDescription* stsd = dynamic_cast<SampleDescription*>(all.get("stsd"));
//     AVCSampleEntry* avc1 = dynamic_cast<AVCSampleEntry*>(stsd->get("avc1"));
//     AVCConfiguration* config = dynamic_cast<AVCConfiguration*>(avc1->getConfig());
//     int length_size = config->getLengthSize();
//     std::cout << "length_size="<<length_size<<std::endl;
    
    SkipContents* mdat = dynamic_cast<SkipContents*>(all.get("mdat"));
    if(mdat != NULL) {
        ArrayByteSource array(mdat->getBytes(), mdat->getByteCount());


    
        while(array.getRemaining()>0) {
            uint32_t size = array.readUint32();
            std::cout << "size="<<size<<std::endl;
            SubByteSource sub("nalu", array, size);
            
            NALU nalu;
            nalu.read(sub);
            
            int remaining = sub.getRemaining();
            //std::cout << "remaining="<<remaining<<" array remainging="<<array.getRemaining()<<std::endl;
            uint8_t tmp[remaining];
            sub.read(tmp, remaining);
        }
    }
    
    
} // end of main
