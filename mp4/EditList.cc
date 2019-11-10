#include "EditList.h"

#include "MP4Exception.h"
  
/******************************************************************************//**
*
**********************************************************************************/
EditList::EditList(uint32_t size) 
                : Contents("stss", size) {
    
} // end of constructor

/******************************************************************************//**
*
**********************************************************************************/
void EditList::read(ByteSource& source) {
    
    version = source.readUint8();
    flags   = source.readBits(24);
    
    std::cout <<"version="<<version<<" flags="<<flags<<std::endl;
    
    entry_count = source.readUint32();
    std::cout << "entry_count="<<entry_count<<std::endl;
    
    for(int i=0; i<(int)entry_count; ++i) {
        if(version == 1) {
            uint64_t segment_duration = source.readUint64();
            int64_t media_time = source.readInt64();  
            std::cout << i<<" duration="<<segment_duration<<" media_time="<<media_time<<std::endl;

            
        } else if(version == 0) {
            uint32_t segment_duration = source.readUint32();
            int32_t media_time = source.readInt32();
            std::cout << i<<" duration="<<segment_duration<<" media_time="<<media_time<<std::endl;

        } else {
            throw MP4Exception("Unsupported version");
        }
    
        int16_t media_rate_integer  = source.readInt16();
        int16_t media_rate_fraction = source.readInt16();
    
        std::cout << "integer="<<media_rate_integer<<" fraction="<<media_rate_fraction<<std::endl;
        
    } // end of loop over entries
    
} // end if read method
