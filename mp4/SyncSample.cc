#include "SyncSample.h"

#include "Box.h"
  
/******************************************************************************//**
*
**********************************************************************************/
SyncSample::SyncSample() 
          : Contents("stss") {
    
} // end of constructor

/******************************************************************************//**
*
**********************************************************************************/
void SyncSample::clear() {
    
    entries.clear();
    
} // end of clear method
    
/******************************************************************************//**
*
**********************************************************************************/
void SyncSample::add(uint32_t entry_size) {
    
    entries.push_back(entry_size);
    
} // end of add method

/******************************************************************************//**
*
**********************************************************************************/
uint64_t SyncSample::getSize() const {
    
    return 8 + entries.size()*4;

} // end of getSize method

/******************************************************************************//**
*
**********************************************************************************/
void SyncSample::read(ByteSource& source) {
    
    version = source.readUint8();
    flags   = source.readBits(24);
    
    std::cout <<"version="<<version<<" flags="<<flags<<std::endl;
    
    uint32_t entry_count = source.readUint32();
    std::cout << "entry_count="<<entry_count<<std::endl;
    for(int i=0; i<(int)entry_count; ++i) {
        uint32_t sample_number = source.readUint32();
        (void)sample_number;
        
    } // end of loop over entries
    
} // end of read method

/******************************************************************************//**
*
**********************************************************************************/
void SyncSample::write(ByteSink& sink) const {
    
    sink.writeUint8(version);
    sink.writeBits(flags, 24);
    
    sink.writeUint32(entries.size());
    for(Entries::const_iterator it = entries.begin(); it != entries.end(); ++it) {
        uint32_t sample_number = *it;
        sink.writeUint32(sample_number);
        
    } // end of loop over entries
    
} // end of read method
