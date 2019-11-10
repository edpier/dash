#include "NALUUnescaper.h"
    
#include <iostream>
    
/**************************************************************************//**
*
******************************************************************************/
NALUUnescaper::NALUUnescaper(ByteSource& source)
             : source(source) {
                 
    nzeros = 0;
    
} // end of constructor

    
/**************************************************************************//**
*
******************************************************************************/
void NALUUnescaper::read(unsigned char* data, int length) {
    
    for(int i=0; i<length; ) {
        uint8_t byte = source.readUint8();

        /****************************
        * should we keep this byte? *
        ****************************/
        if(nzeros != 2 || byte != 3) {
            data[i++] = byte;
        }
        
        /******************
        * count the zeros *
        ******************/
        if(byte == 0) ++nzeros;
        else          nzeros = 0;

    } // end of loop over bytes
    
} // end of read method
