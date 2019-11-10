#include "SubByteSource.h"

#include "MP4Exception.h"

/******************************************************************************//**
*
**********************************************************************************/
SubByteSource::SubByteSource(const std::string& name, ByteSource& source, uint64_t length) 
             : name(name),
               source(source),
               remaining(length) {
    
} // end of SubByteSource method
        
/******************************************************************************//**
*
**********************************************************************************/
bool SubByteSource::hasMoreData() const {
    
    return remaining >0;
    
} // end of hasMoreData method
        
/******************************************************************************//**
*
**********************************************************************************/
uint64_t SubByteSource::getRemaining() const { return remaining; }
    
/******************************************************************************//**
*
**********************************************************************************/
void SubByteSource::read(unsigned char* data, int length) {
    
    if(length>(int)remaining) {
        throw MP4Exception("Overran end of substream "+name);
    }
    
    source.read(data, length);
    
    remaining -= length;
    
} // end of read method
