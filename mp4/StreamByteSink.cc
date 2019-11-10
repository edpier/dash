#include "StreamByteSink.h"

#include "MP4Exception.h"
    
/******************************************************************************//**
* @brief constructor
* @details This class takes ownership of the stream.
**********************************************************************************/
StreamByteSink::StreamByteSink(std::ostream* out) {
    
    this->out = out;
    
} //  end of constructor
    
    
/******************************************************************************//**
*
**********************************************************************************/
StreamByteSink::~StreamByteSink() {
    
    delete out;
    
} // end of destructor
    
/******************************************************************************//**
*
**********************************************************************************/
void StreamByteSink::write(const unsigned char* data, int length) {
    
    out->write((char*)data, length); 
       
    if(!out->good()) {
        throw MP4Exception("I/O error");
    }

} // end of write method
