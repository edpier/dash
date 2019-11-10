#ifndef BYTE_SOURCE_H
#define BYTE_SOURCE_H

#include <cstdint>
#include <string>

/**************************************************************************//**
*
******************************************************************************/
class ByteSource {
    
private:
    
public:
    ByteSource();
    virtual ~ByteSource() {}
    
    virtual void read(unsigned char* data, int length) =0;
    
    virtual uint64_t getRemaining() const;
        
    int16_t readInt16();
    int32_t readInt32();
    uint64_t readInt64();
    
    uint8_t readUint8();
    int16_t readUint16();
    uint32_t readUint32();
    uint64_t readUint64();
    
    uint64_t readBits(int nbits);
    
    void readString(std::string& string);
    void readString(std::string& string, int length);
}; // end of ByteSource class

#endif
