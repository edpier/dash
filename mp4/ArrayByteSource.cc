#include "ArrayByteSource.h"

#include <cstring>

#include "MP4Exception.h"

/**************************************************************************//**
*
******************************************************************************/
ArrayByteSource::ArrayByteSource(uint8_t* data, int size) {
    
    this->data = data;
    this->size = size;
    
    index = 0;
    
} // end of constructor

/**************************************************************************//**
*
******************************************************************************/
void ArrayByteSource::read(unsigned char* data, int length) {
    
    if(index+length > size) {
        throw MP4Exception("Reading past end of array");
    }
    
    memcpy(data, this->data+index, length);
    
    index += length;
    
} // end of read method

/**************************************************************************//**
*
******************************************************************************/
uint64_t ArrayByteSource::getRemaining() const {
    
    return size - index;
    
} // end of getRemaining
