#ifndef SAMPLE_TO_CHUNK_H
#define SAMPLE_TO_CHUNK_H

#include "Contents.h"

#include <vector>
  
/**************************************************************************************//**
* table entry
******************************************************************************************/
typedef struct {

    uint32_t first_chunk;
    uint32_t samples_per_chunk;
    uint32_t sample_description_index;
        
} SampleToChunkEntry;
  
/**************************************************************************************//**
*
******************************************************************************************/
class SampleToChunk : public Contents {
    
private:
    int version;
    uint32_t flags;

    typedef std::vector<SampleToChunkEntry*> Entries;
    Entries entries;
    
public:
    SampleToChunk();
    virtual ~SampleToChunk() {}
    
    void clear();
    void add(uint32_t first_chunk, 
             uint32_t samples_per_chunk, 
             uint32_t sample_description_index);

    uint64_t getSize() const;
    void read(ByteSource& source);
    void write(ByteSink& sink) const;
    
}; // end of SampleToChunk class
#endif
