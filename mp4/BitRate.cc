#include "BitRate.h"

/**************************************************************************//**
*
******************************************************************************/
BitRate::BitRate() 
       : Contents("btrt") {
           
} // end of constructor

    
/**************************************************************************//**
*
******************************************************************************/
uint64_t BitRate::getSize() const { return 32*3; }
    
/**************************************************************************//**
*
******************************************************************************/
void BitRate::read(ByteSource& source) {
    
    decoding_buffer_size = source.readUint32();
    max_bit_rate         = source.readUint32();
    avg_bit_rate         = source.readUint32();
    
    std::cout <<"decoding_buffer_size="<<decoding_buffer_size<<std::endl;
    std::cout <<"max_bit_rate="<<max_bit_rate<<std::endl;
    std::cout <<"avg_bit_rate="<<avg_bit_rate<<std::endl;
    
} // end of read method
    
/**************************************************************************//**
*
******************************************************************************/
void BitRate::write(ByteSink& sink) const {
    
} // end of write method
