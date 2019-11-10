#include "SampleSize.h"

#include "Box.h"
  
/******************************************************************************//**
*
**********************************************************************************/
SampleSize::SampleSize() 
                : Contents("stsz") {
                    
    sample_size = 0;
    
} // end of constructor

/******************************************************************************//**
*
**********************************************************************************/
void SampleSize::clear() {
    
    entries.clear();
    
} // end of clear method
    
/******************************************************************************//**
*
**********************************************************************************/
void SampleSize::add(uint32_t entry_size) {
    
    entries.push_back(entry_size);
    
} // end of add method

/******************************************************************************//**
*
**********************************************************************************/
uint64_t SampleSize::getSize() const {
    
    uint32_t size = 12;
    if(sample_size == 0) size +=  entries.size()*4;
    
    return size;
    
} // end of getSize method

/******************************************************************************//**
*
**********************************************************************************/
void SampleSize::read(ByteSource& source) {
    
    version = source.readUint8();
    flags   = source.readBits(24);
    
    std::cout <<"version="<<version<<" flags="<<flags<<std::endl;
    
    sample_size = source.readUint32();
    uint32_t sample_count = source.readUint32();
    
    std::cout <<"sample_size="<<sample_size<<" sample_count="<<sample_count<<std::endl;
    
    if(sample_size == 0) {
        for(int i=0; i<(int)sample_count; ++i) {
            uint32_t entry_count = source.readUint32();
            add(entry_count);
        }
    }
    
} //end of read method
    
/******************************************************************************//**
*
**********************************************************************************/
void SampleSize::write(ByteSink& sink) const {

    sink.writeUint8(version);
    sink.writeBits(flags, 24);

    sink.writeUint32(sample_size);
    sink.writeUint32(entries.size());
    
    if(sample_size == 0) {
        for(Entries::const_iterator it = entries.begin(); it != entries.end(); ++it) {
            uint32_t entry_count = *it;
            sink.writeUint32(entry_count);
        }
    }
} // end of write method
