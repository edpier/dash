#include "SampleTable.h"

/**************************************************************************//**
*
******************************************************************************/
SampleTable::SampleTable()
           : Contents("ctts") {
    
    version = 0;
    flags = 0;
    
} // end of constructor


/**************************************************************************//**
*
******************************************************************************/
SampleTable::~SampleTable() {
    
} // end of destructor

/**************************************************************************//**
*
******************************************************************************/
uint64_t SampleTable::getSize() const {
    
    return 0;
    
} // end of getSize method

/**************************************************************************//**
*
******************************************************************************/
void SampleTable::read(ByteSource& source) {
    
    version = source.readUint8();
    flags   = source.readBits(24);
    
    std::cout <<"version="<<version<<" flags="<<flags<<std::endl;
    
    uint32_t entry_count = source.readUint32();
    std::cout << "entry_count="<<entry_count<<std::endl;
    
    for(uint32_t i=0; i<entry_count; ++i) {
        uint32_t sample_count  = source.readUint32();
        uint32_t sample_offset = source.readUint32();
        
        std::cout <<"    "<<i<<" sample_count="<<sample_count<<
                              " sample_offset="<<sample_offset<<std::endl;
        
    } // end of loop over entries
    
} // end of read method

/**************************************************************************//**
*
******************************************************************************/
void SampleTable::write(ByteSink& sink) const {
    
    sink.writeUint8(version);
    sink.writeBits(flags, 24);
    
} // end fo write method
