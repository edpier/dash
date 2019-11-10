#include "StreamByteSource.h"

#include <cstdio>
#include <iomanip>

#include "MP4Exception.h"
    
/*******************************************************************************//**
* @brief constructor
* @details This class takes ownership of the stream.
***********************************************************************************/
StreamByteSource::StreamByteSource(std::istream* in) {
    
    this->in = in;
    
} //  end of constructor
    
    
/*******************************************************************************//**
*
***********************************************************************************/
StreamByteSource::~StreamByteSource() {
    
    delete in;
    
} // end of destructor

/**************************************************************************//**
*
******************************************************************************/
uint64_t StreamByteSource::getRemaining() const { 
    
    if(in->peek() == EOF) return 0;
    else return ByteSource::getRemaining();
    
} // end of default getRemaining method
    
/*******************************************************************************//**
*
***********************************************************************************/
void StreamByteSource::read(unsigned char* data, int length) {
    
    if(!in->good()) {
        if(in->eof()) throw MP4Exception("End of File");
        else          throw MP4Exception("I/O error");
    }
    
    in->read((char*)data, length);
    
} // end of read method
