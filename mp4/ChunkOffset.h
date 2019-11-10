#ifndef CHUNK_OFFSET_H
#define CHUNK_OFFSET_H

#include "Contents.h"

#include <vector>
  
/**************************************************************************************//**
*
******************************************************************************************/
class ChunkOffset : public Contents {
    
private:
    int version;
    uint32_t flags;
    
    typedef std::vector<uint32_t> Offsets;
    Offsets offsets;

    
public:
    ChunkOffset();
    virtual ~ChunkOffset() {}
    
    void clear();
    void add(uint32_t chunk_offset);

    uint64_t getSize() const;
    void read(ByteSource& source);
    void write(ByteSink& sink) const;
    
}; // end of ChunkOffset class
#endif
