#include "TrackFragmentDecodeTime.h"
          
#include "Box.h"

/******************************************************************************//**
*
**********************************************************************************/
TrackFragmentDecodeTime::TrackFragmentDecodeTime() 
                : Contents("tfdt") {
                    
    version = 0;
    flags = 0;
    base_media_decode_time = 0;
    
} // end of constructor

/******************************************************************************//**
*
**********************************************************************************/
void TrackFragmentDecodeTime::setBaseMediaDecodeTime(uint64_t time) {
    
    this->base_media_decode_time = time;
    
    if(time>>32 != 0) version = 1;
    else              version = 0;
    
} // end of setBaseMediaDecodeTime method


/******************************************************************************//**
*
**********************************************************************************/
uint64_t TrackFragmentDecodeTime::getSize() const {
    
    if(version == 0) return 8;
    else             return 12;
    
} // end of getSize method

/*********************************************************************//**
*
*************************************************************************/
void TrackFragmentDecodeTime::read(ByteSource& source) {
    
    version = source.readUint8();
    flags   = source.readBits(24);
    
    std::cout <<"version="<<version<<" flags="<<flags<<std::endl;
    
    if(version == 0) base_media_decode_time = source.readUint32();
    else             base_media_decode_time = source.readUint64();
    
    std::cout << "base_media_decode_time="<<base_media_decode_time<<std::endl;
    
} //end of read method
    
/*********************************************************************//**
*
*************************************************************************/
void TrackFragmentDecodeTime::write(ByteSink& sink) const {

    sink.writeUint8(version);
    sink.writeBits(flags, 24);
    
    if(version == 0) sink.writeUint32(base_media_decode_time);
    else             sink.writeUint64(base_media_decode_time);



} // end of write method
