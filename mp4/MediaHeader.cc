#include "MediaHeader.h"

#include <sys/time.h>

const uint64_t MediaHeader::MAX32 = 0xffffffff;
  
/*********************************************************************//**
*
*************************************************************************/
MediaHeader::MediaHeader() 
           : Contents("mdhd") {
               
    flags = 0;
    
    uint64_t time = now();
    setCreationTime(time);
    setModificationTime(time);
    setTimescale(90000);
    setDuration(0);   
    
    languages[0] = 4;
    languages[1] = 46;
    languages[2] = 21;
    
} // end of constructor

/*********************************************************************//**
* @details seconds since 1904-01-01 UTC
*************************************************************************/ 
void MediaHeader::setCreationTime(uint64_t time) {
    
    this->creation_time = time;
    updateVersion();
    
} // end of setCreationTime method
   
/*********************************************************************//**
* @details seconds since 1904-01-01 UTC
*************************************************************************/
void MediaHeader::setModificationTime(uint64_t time) {

    this->modification_time = time;
    updateVersion();
    
} // end of setModificationTime method

/*********************************************************************//**
* @details ticks per second
*************************************************************************/
void MediaHeader::setTimescale(uint32_t timescale) {
    
    this->timescale = timescale;
    
} // end of setTimescale


/*********************************************************************//**
* @details ticks
*************************************************************************/
void MediaHeader::setDuration(uint64_t duration) {
    
    this->duration = duration;
    updateVersion();
    
} // end of setDuration method
  
/*********************************************************************//**
*
*************************************************************************/
uint64_t MediaHeader::getSize() const {
    
    if(version == 0) return 24;
    else             return 36;
    
} // end of getSize method
  
/*********************************************************************//**
*
*************************************************************************/
void MediaHeader::read(ByteSource& source) {
    
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
    std::cout << "timescale "<<timescale<<std::endl;
    std::cout << "duration "<<duration<<std::endl;
    
    uint16_t bits = source.readUint16();
    int mask = (1<<6)-1;
    for(int i=2; i>=0; --i) {
        
        languages[i] = bits&mask;
        bits >>= 5;
        
        std::cout << "language = "<<(int)languages[i]<<std::endl;
    }
        
    source.readUint16();
    
} // end of read method

/*********************************************************************//**
*
*************************************************************************/
void MediaHeader::write(ByteSink& sink) const {
    
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
    
    
    uint16_t bits = 0;
    int mask = (1<<6)-1;
    for(int i=2; i>=0; --i) {
        
        bits <<=5;
        bits |= languages[i]&mask;

    }
    sink.writeUint16(bits);
    
        
    sink.writeUint16(0);
    
} // end of write

/*********************************************************************//**
*
*************************************************************************/
uint64_t MediaHeader::now() {
    
    struct timeval t;
    gettimeofday(&t, NULL);
    
    uint64_t time = t.tv_sec;
    
    time += 2082844800l; // offset between 1904 and 1970
    
    return time;

    
} // end of now method

/*********************************************************************//**
*
*************************************************************************/
void MediaHeader::updateVersion() {
    
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
