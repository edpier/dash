#include "ByteSource.h"

#include <iostream>

#include "MP4Exception.h"

/**************************************************************************//**
*
******************************************************************************/
ByteSource::ByteSource() {
    
} // end of constructor

/**************************************************************************//**
*
******************************************************************************/
uint64_t ByteSource::getRemaining() const { 
    
    uint64_t remaining = 0;
    remaining = ~remaining; // max value
    return remaining;
    
} // end of default getRemaining method

/**************************************************************************//**
*
******************************************************************************/
int16_t ByteSource::readInt16() {
        
    int16_t value;
    unsigned char* bytes = (unsigned char*)(&value);
    unsigned char tmp[2];
    
    read(tmp, 2);
    
    bytes[0] = tmp[1];
    bytes[1] = tmp[0];

    return value;
    
} // end of readInt16 method
    
/**************************************************************************//**
*
******************************************************************************/
int32_t ByteSource::readInt32() {
    
    int32_t value;
    unsigned char* bytes = (unsigned char*)(&value);
    unsigned char tmp[4];
    
    read(tmp, 4);
    
    bytes[0] = tmp[3];
    bytes[1] = tmp[2];
    bytes[2] = tmp[1];
    bytes[3] = tmp[0];
    
    return value;
    
} // end of readInt32 method

/**************************************************************************//**
*
******************************************************************************/
uint64_t ByteSource::readInt64() {
    
    int64_t value;
    unsigned char* bytes = (unsigned char*)(&value);
    unsigned char tmp[8];
    
    read(tmp, 8);
    
    bytes[0] = tmp[7];
    bytes[1] = tmp[6];
    bytes[2] = tmp[5];
    bytes[3] = tmp[4];
    bytes[4] = tmp[3];
    bytes[5] = tmp[2];
    bytes[6] = tmp[1];
    bytes[7] = tmp[0];
    
    return value;
    
} // end of readInt64

/**************************************************************************//**
*
******************************************************************************/
uint8_t ByteSource::readUint8() {
    
    uint8_t value;
    read((unsigned char*)(&value), 1);

    return value;
    
} // end of readUint8

/**************************************************************************//**
*
******************************************************************************/
int16_t ByteSource::readUint16() {
        
    uint16_t value;
    unsigned char* bytes = (unsigned char*)(&value);
    unsigned char tmp[2];
    
    read(tmp, 2);
    
    bytes[0] = tmp[1];
    bytes[1] = tmp[0];

    return value;
    
} // end of readInt16 method

/**************************************************************************//**
*
******************************************************************************/
uint32_t ByteSource::readUint32() {
    
    uint32_t value;
    unsigned char* bytes = (unsigned char*)(&value);
    unsigned char tmp[4];
    
    //std::cout << "reading 4"<<std::endl;
    read(tmp, 4);
    //std::cout << "done reading 4"<<std::endl;
    
    bytes[0] = tmp[3];
    bytes[1] = tmp[2];
    bytes[2] = tmp[1];
    bytes[3] = tmp[0];
    
    return value;
    
} // end of readUint32

/**************************************************************************//**
*
******************************************************************************/
uint64_t ByteSource::readUint64() {
    
    uint64_t value;
    unsigned char* bytes = (unsigned char*)(&value);
    unsigned char tmp[8];
    
    read(tmp, 8);
    
    bytes[0] = tmp[7];
    bytes[1] = tmp[6];
    bytes[2] = tmp[5];
    bytes[3] = tmp[4];
    bytes[4] = tmp[3];
    bytes[5] = tmp[2];
    bytes[6] = tmp[1];
    bytes[7] = tmp[0];
    
    return value;
    
} // end of readUint64

/**************************************************************************//**
*
******************************************************************************/
uint64_t ByteSource::readBits(int nbits) {
    
    if(nbits%8 != 0) {
        throw MP4Exception("Bits not a multiple of 8");
    }
    
    int nbytes = nbits/8;
    if(nbytes>8) {
        throw MP4Exception("Too many bits");
    }
    
    uint64_t bits=0;
    unsigned char bytes[nbytes];
    read(bytes, nbytes);
    
    for(int i=0; i<nbytes; ++i) {
        bits <<=8;
        bits |= bytes[i];
    }
    
    return bits;
    
    
} // end of readBits method

/**************************************************************************//**
*
******************************************************************************/
void ByteSource::readString(std::string& string) {
    
    string.clear();
    
    while(true) {
        unsigned char c;
        read(&c, 1);

        if(c == '\0') return;
        else string += c;
        
        //std::cout <<string<<std::endl;
        
    } // end of loop over characters
        
    
    
} // end of readString method

/**************************************************************************//**
*
******************************************************************************/
void ByteSource::readString(std::string& string, int length) {
    
    string.clear();
    
    for(int i=0; i<length; ++i) {
        char c = readUint8();
        if(c != '\0') string += c;
        
    } 
    
} // end of fixed length readString method
