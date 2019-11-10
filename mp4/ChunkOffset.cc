#include "ChunkOffset.h"

#include "Box.h"
  
/******************************************************************************//**
*
**********************************************************************************/
ChunkOffset::ChunkOffset() 
           : Contents("stco") {
    
} // end of constructor
    
/******************************************************************************//**
*
**********************************************************************************/
void ChunkOffset::clear() {
    
    offsets.clear();
    
} // end of clear method
        
/******************************************************************************//**
*
**********************************************************************************/
void ChunkOffset::add(uint32_t chunk_offset) {
    
    offsets.push_back(chunk_offset);
    
} // end of add method
    
/******************************************************************************//**
*
**********************************************************************************/
uint64_t ChunkOffset::getSize() const {
    
    return 8 + offsets.size()*4;
    
} // end of getSize method
    
/******************************************************************************//**
*
**********************************************************************************/
void ChunkOffset::read(ByteSource& source) {
    
    version = source.readUint8();
    flags   = source.readBits(24);
    
    std::cout <<"version="<<version<<" flags="<<flags<<std::endl;
    
    uint32_t entry_count = source.readUint32();
    
    for(int i=0; i<(int)entry_count; ++i) {
        uint32_t chunk_offset = source.readUint32();
        std::cout << i<<" chunk_offset="<<chunk_offset<<std::endl;
        
        add(chunk_offset);
    }
    
} // end of read method
    
/******************************************************************************//**
*
**********************************************************************************/
void ChunkOffset::write(ByteSink& sink) const {
    
    sink.writeUint8(version);
    sink.writeBits(flags, 24);

    sink.writeUint32(offsets.size());
    
    for(Offsets::const_iterator it = offsets.begin(); it != offsets.end(); ++it) {
        uint32_t chunk_offset = *it;

        sink.writeUint32(chunk_offset);
    }
    
} // end of write method
