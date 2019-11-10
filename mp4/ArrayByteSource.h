#ifndef ARRAY_BYTE_SOURCE_H
#define ARRAY_BYTE_SOURCE_H

#include "ByteSource.h"

#include <cstdint>
#include <string>

/**************************************************************************//**
*
******************************************************************************/
class ArrayByteSource : public ByteSource {
    
private:
    int size;
    uint8_t* data;
    int index;
    
public:
    ArrayByteSource(uint8_t* data, int size);
    virtual ~ArrayByteSource() {}
    
    virtual void read(unsigned char* data, int length);
    
    virtual uint64_t getRemaining() const;
        

}; // end of ArrayByteSource class

#endif
