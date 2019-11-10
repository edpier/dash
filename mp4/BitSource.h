#ifndef BIT_SOURCE
#define BIT_SOURCE

#include "ByteSource.h"
    
/**************************************************************************//**
*
******************************************************************************/
class BitSource {
    
private:
    ByteSource& bytes;
    
    uint8_t byte;
    int index;
    
public:
    BitSource(ByteSource& bytes);
    virtual ~BitSource() {}
    
    unsigned int readBit();
    
    uint32_t readU(int nbits);
    uint32_t readUE();
     int32_t readSE();
    
}; // end of BitSource class


#endif
