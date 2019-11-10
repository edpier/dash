#ifndef BYTE_SINK_H
#define BYTE_SINK_H

#include <cstdint>
#include <string>

/*******************************************************************************//**
*
***********************************************************************************/
class ByteSink {
    
private:
    
public:
    ByteSink();
    virtual ~ByteSink() {}
    
    virtual void write(const unsigned char* data, int length) =0;
    
    void writeInt16(int16_t value);
    void writeInt32(int32_t value);
    void writeInt64(uint64_t value);
    
    void writeUint8(uint8_t value);
    void writeUint16(int16_t value);
    void writeUint32(uint32_t value);
    void writeUint64(uint64_t value);
    
    void writeBits(uint64_t value, int nbits);
    
    void writeString(const std::string& string);
    
}; // end of ByteSink class

#endif
