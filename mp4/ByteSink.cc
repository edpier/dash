#include "ByteSink.h"

#include <iostream>

#include "MP4Exception.h"

/******************************************************************************//**
*
**********************************************************************************/
ByteSink::ByteSink() {
    
} // end of constructor

/******************************************************************************//**
*
**********************************************************************************/
void ByteSink::writeInt16(int16_t value) {
        
    unsigned char* bytes = (unsigned char*)(&value);
    unsigned char tmp[2];
    
    tmp[1] = bytes[0];
    tmp[0] = bytes[1];
    
    write(tmp, 2);
    
} // end of writeInt16 method
    
/*******************************************************************************//**
*
***********************************************************************************/
void ByteSink::writeInt32(int32_t value) {

    unsigned char* bytes = (unsigned char*)(&value);
    unsigned char tmp[4];
    
    tmp[3] = bytes[0];
    tmp[2] = bytes[1];
    tmp[1] = bytes[2];
    tmp[0] = bytes[3];
    
    write(tmp, 4);

} // end of writeInt32 method

/*******************************************************************************//**
*
***********************************************************************************/
void ByteSink::writeInt64(uint64_t value) {

    unsigned char* bytes = (unsigned char*)(&value);
    unsigned char tmp[8];
       
    tmp[7] = bytes[0];
    tmp[6] = bytes[1];
    tmp[5] = bytes[2];
    tmp[4] = bytes[3];
    tmp[3] = bytes[4];
    tmp[2] = bytes[5];
    tmp[1] = bytes[6];
    tmp[0] = bytes[7];
    
    write(tmp, 8);

} // end of writeInt64

/*******************************************************************************//**
*
***********************************************************************************/
void ByteSink::writeUint8(uint8_t value) {

    write((unsigned char*)(&value), 1);
    
} // end of writeUint8

/*******************************************************************************//**
*
***********************************************************************************/
void ByteSink::writeUint16(int16_t value) {
        
    unsigned char* bytes = (unsigned char*)(&value);
    unsigned char tmp[2];
    
    tmp[1] = bytes[0];
    tmp[0] = bytes[1];
    
    write(tmp, 2);

} // end of writeInt16 method

/*******************************************************************************//**
*
***********************************************************************************/
void ByteSink::writeUint32(uint32_t value) {

    unsigned char* bytes = (unsigned char*)(&value);
    unsigned char tmp[4];
     
    tmp[3] = bytes[0];
    tmp[2] = bytes[1];
    tmp[1] = bytes[2];
    tmp[0] = bytes[3];
    
    write(tmp, 4);

} // end of writeUint32

/*******************************************************************************//**
*
***********************************************************************************/
void ByteSink::writeUint64(uint64_t value) {

    unsigned char* bytes = (unsigned char*)(&value);
    unsigned char tmp[8];
     
    tmp[7] = bytes[0];
    tmp[6] = bytes[1];
    tmp[5] = bytes[2];
    tmp[4] = bytes[3];
    tmp[3] = bytes[4];
    tmp[2] = bytes[5];
    tmp[1] = bytes[6];
    tmp[0] = bytes[7];
    
    write(tmp, 8);
    
} // end of writeUint64

/*******************************************************************************//**
*
***********************************************************************************/
void ByteSink::writeBits(uint64_t value, int nbits) {
    
    if(nbits%8 != 0) {
        throw MP4Exception("Bits not a multiple of 8");
    }
    
    int nbytes = nbits/8;
    if(nbytes>8) {
        throw MP4Exception("Too many bits");
    }
    
    unsigned char bytes[nbytes];
    for(int i=0; i<nbytes; ++i) {
        bytes[nbytes-i-1] = value&0xff;
        value >>=8;
    }

    write(bytes, nbytes);

} // end of writeBits method

/*******************************************************************************//**
*
***********************************************************************************/
void ByteSink::writeString(const std::string& string) {
    
    write((const unsigned char*)(string.c_str()), string.length()+1);

} // end of writeString method
