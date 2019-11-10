#include "VideoMediaHeader.h"

#include "Box.h"
  
/**************************************************************************************//**
*
******************************************************************************************/
VideoMediaHeader::VideoMediaHeader() 
                : Contents("vmhd") {
    
    graphics_mode = 0;
    opcolor_r = 0;
    opcolor_g = 0;
    opcolor_b = 0;
    
} // end of constructor

/**************************************************************************************//**
*
******************************************************************************************/
uint64_t VideoMediaHeader::getSize() const {
    
    return 12;
    
} // end of getSize method

/**************************************************************************************//**
*
******************************************************************************************/
void VideoMediaHeader::read(ByteSource& source) {
    
    version = source.readUint8();
    flags   = source.readBits(24);
    
    std::cout <<"version="<<version<<" flags="<<flags<<std::endl;
    
    graphics_mode = source.readUint16();
    opcolor_r = source.readUint16();
    opcolor_g = source.readUint16();
    opcolor_b = source.readUint16();
    
    std::cout << "graphics_mode = "<<graphics_mode<<std::endl;
    
    std::cout<<"opcolor ="<<opcolor_r<<" "<<opcolor_g<<" "<<opcolor_b<<std::endl;
    
} // end of read method

/**************************************************************************************//**
*
******************************************************************************************/
void VideoMediaHeader::write(ByteSink& sink) const {
    
    sink.writeUint8(version);
    sink.writeBits(flags, 24);

    sink.writeUint16(graphics_mode);
    
    sink.writeUint16(opcolor_r);
    sink.writeUint16(opcolor_g);
    sink.writeUint16(opcolor_b);
    
} // end of write method
