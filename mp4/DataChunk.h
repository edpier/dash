#ifndef DATA_CHUNK_H
#define DATA_CHUNK_H

#include <vector>
#include <stdint.h>

#include "ByteSink.h"
#include "ByteSource.h"
  
/**************************************************************************//**
*
******************************************************************************/
class DataChunk {
    
private:
    
    uint32_t size;
    uint8_t* data;

public:
    DataChunk();
    virtual ~DataChunk();
    
    void setSize(uint32_t size);
    uint8_t* getData();
    const uint8_t* getData() const;
    
    uint64_t getSize() const;
    uint64_t getTotalSize() const;
    void read(ByteSource& source);
    void write(ByteSink& sink) const;
    
}; // end of AVCConfigurationclass
#endif
