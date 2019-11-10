#include "ByteSource.h"

#include <iostream>

/**************************************************************************************//**
*
******************************************************************************************/
class StreamByteSource : public ByteSource {
    
private:
    std::istream* in;
    
public:
    StreamByteSource(std::istream* in);
    virtual ~StreamByteSource();
    
    uint64_t getRemaining() const;
    void read(unsigned char* data, int length);
    
    
}; // end of StreamByteSource
