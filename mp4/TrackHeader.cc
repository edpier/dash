#include "TrackHeader.h"

#include <sys/time.h>

const uint64_t TrackHeader::MAX32 = 0xffffffff;

/**************************************************************************************//**
*
******************************************************************************************/
TrackHeader::TrackHeader() 
           : Contents("tkhd") {
               
    flags = 0;
    
    uint64_t time = now();
    setCreationTime(time);
    setModificationTime(time);
    setTimescale(9000);
    setDuration(0);
    
    layer = 0;
    alternate_group = 0;
    volume = 0; // 0x0100 if audio
              
       
    matrix[0] = 0x00010000;
    matrix[1] = 0;
    matrix[2] = 0;
    matrix[3] = 0;
    matrix[4] = 0x00010000;
    matrix[5] = 0;
    matrix[6] = 0;
    matrix[7] = 0;
    matrix[8] = 0x40000000;
    
    setDimensions(1920, 1080);
    
} // end of constructor

/**************************************************************************************//**
* @details seconds since 1904-01-01 UTC
******************************************************************************************/ 
void TrackHeader::setCreationTime(uint64_t time) {
    
    this->creation_time = time;
    updateVersion();
    
} // end of setCreationTime method
   
/**************************************************************************************//**
* @details seconds since 1904-01-01 UTC
******************************************************************************************/
void TrackHeader::setModificationTime(uint64_t time) {

    this->modification_time = time;
    updateVersion();
    
} // end of setModificationTime method

/**************************************************************************************//**
* @details ticks per second
******************************************************************************************/
void TrackHeader::setTimescale(uint32_t timescale) {
    
    this->timescale = timescale;
    
} // end of setTimescale


/**************************************************************************************//**
* @details ticks
******************************************************************************************/
void TrackHeader::setDuration(uint64_t duration) {
    
    this->duration = duration;
    updateVersion();
    
} // end of setDuration method
  
/**************************************************************************************//**
*
******************************************************************************************/
void TrackHeader::setDimensions(double width, double height) {
    
    double scale = 1<<16;
    this->width = width*scale;
    this->height = height*scale;
    
} // end of setDimensions method
  
/**************************************************************************************//**
*
******************************************************************************************/ 
uint64_t TrackHeader::getSize() const {
    
    if(version == 0) return 84;
    else             return 96;
    
} // end of getSize method
  
/**************************************************************************************//**
*
******************************************************************************************/  
void TrackHeader::read(ByteSource& source) {
    
    version = source.readUint8();
    flags   = source.readBits(24);
    
    std::cout << "version="<<version<<std::endl;
  
    if(version == 0) {
        creation_time     = source.readUint32();
        modification_time = source.readUint32();
        timescale         = source.readUint32();
        duration          = source.readUint32();
    } else {
        creation_time     = source.readUint64();
        modification_time = source.readUint64();
        timescale         = source.readUint32();
        duration          = source.readUint64();
    }
    
    std::cout << "creation "<<creation_time<<std::endl;
    std::cout << "mod "<<modification_time<<std::endl;
    std::cout << "timscale "<<timescale<<std::endl;
    std::cout << "duration "<<duration<<std::endl;
    
    source.readUint32();
    source.readUint32();
    
    layer           = source.readInt16();
    alternate_group = source.readInt16();
    volume          = source.readInt16();
    
    std::cout << "layer="<<layer<<" alt_group="<<alternate_group<<" volume="<<volume<<std::endl;
    
    source.readUint16();
    source.readUint32(); // this wasn't in the doc, but is needed
    //uint32_t reserved = source.readUint32();
    //std::cout << "reserved="<<reserved<<std::endl;
    
    for(int i=0; i<9; ++i) {
        matrix[i] = source.readInt32();
        std::cout << i <<" matrix="<<matrix[i]<<std::endl;
    }
    
    width  = source.readUint32();
    height = source.readUint32();
    
    std::cout << "width="<<(width>>16)<<" height="<<(height>>16)<<std::endl;
    
} // end of read method
  
/**************************************************************************************//**
*
******************************************************************************************/  
void TrackHeader::write(ByteSink& sink) const {
    
    sink.writeUint8(version);
    sink.writeBits(flags, 24);

    if(version == 0) {
        sink.writeUint32(creation_time);
        sink.writeUint32(modification_time);
        sink.writeUint32(timescale);
        sink.writeUint32(duration);
    } else {
        sink.writeUint64(creation_time);
        sink.writeUint64(modification_time);
        sink.writeUint32(timescale);
        sink.writeUint64(duration);
    }
    
    sink.writeUint32(0);
    sink.writeUint32(0);
    
    sink.writeInt16(layer);
    sink.writeInt16(alternate_group);
    sink.writeInt16(volume);

    sink.writeUint16(0);
    sink.writeUint32(0); // this wasn't in the doc, but is needed
    
    for(int i=0; i<9; ++i) {
       sink.writeInt32(matrix[i]);
    }
    
    sink.writeUint32(width);
    sink.writeUint32(height);
    
} // end of write method

/**************************************************************************************//**
*
******************************************************************************************/
uint64_t TrackHeader::now() {
    
    struct timeval t;
    gettimeofday(&t, NULL);
    
    uint64_t time = t.tv_sec;
    
    time += 2082844800l; // offset between 1904 and 1970
    
    return time;

    
} // end of now method

/**************************************************************************************//**
*
******************************************************************************************/
void TrackHeader::updateVersion() {
    
    if(creation_time > MAX32 ||
       modification_time > MAX32 ||
       duration          > MAX32   ) {
        /**********************
        * we need the big one *
        **********************/
        version = 1;
    } else {
        /***********************
        * the little one is OK *
        ***********************/
        version = 0;
    }
} // end of updateVersion method
