#include "BitSource.h"

#include <iostream>
    
/**************************************************************************//**
*
******************************************************************************/
BitSource::BitSource(ByteSource& bytes)
         : bytes(bytes) {
    
    byte = 0;
    index = -1;
    
} // end of constructor

/**************************************************************************//**
*
******************************************************************************/
unsigned int BitSource::readBit() {
    
    if(index == -1) {
        /****************************
        * time to read another byte *
        ****************************/
        byte = bytes.readUint8();
        index = 7;
    }
    

    return (byte>>(index--))&1;
    
    
} // end of readBit method
    
/**************************************************************************//**
*
******************************************************************************/
uint32_t BitSource::readU(int nbits) {
    
    uint32_t bits = 0;
    for(int i=0; i<nbits; ++i) {
        
        bits <<=1;
        bits |= readBit();
        
    } // end of loop over bits
    
    return bits;
    
} // end of readUnsignedBits method
    
/**************************************************************************//**
*
******************************************************************************/
uint32_t BitSource::readUE() {
    
    /******************
    * count the zeros *
    ******************/
    uint32_t nzeros = 0;
    while(readBit() == 0) ++nzeros;
    
    return (1<<nzeros) -1 + readU(nzeros);
    
} // end of read unsigned exponential Golomb method
    
/**************************************************************************//**
*
******************************************************************************/
int32_t BitSource::readSE() {
    
    /******************
    * count the zeros *
    ******************/
    uint32_t code = readUE();
    
    int32_t value = (code+1)/2;
    if(code%2 == 0) value = -value;
    
    return value;

    
} // end of read unsigned exponential Golomb method
