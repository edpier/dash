#include "ByteSink.h"

#include <iostream>

/**************************************************************************************//**
*
******************************************************************************************/
class StreamByteSink : public ByteSink {
    
private:
    std::ostream* out;
    
public:
    StreamByteSink(std::ostream* out);
    virtual ~StreamByteSink();
    
    virtual void write(const unsigned char* data, int length);
    
    
}; // end of StreamByteSink
