#include "MovieHeader.h"

#include <sys/time.h>

const uint64_t MovieHeader::MAX32 = 0xffffffff;

/******************************************************************************//**
*
**********************************************************************************/
MovieHeader::MovieHeader()
           : Contents("mvhd") {
               
    flags = 0;
    
    matrix[0] = 0x00010000;
    matrix[1] = 0;
    matrix[2] = 0;
    matrix[3] = 0;
    matrix[4] = 0x00010000;
    matrix[5] = 0;
    matrix[6] = 0;
    matrix[7] = 0;
    matrix[8] = 0x40000000;
    
    rate = 0x00010000;
    volume = 0x0100;
    
    uint64_t time = now();
    setCreationTime(time);
    setModificationTime(time);
    setTimescale(9000);
    setDuration(0);
    
    next_track_id = 2;
    
} // end of constructor

   
/******************************************************************************//**
* @details seconds since 1904-01-01 UTC
**********************************************************************************/ 
void MovieHeader::setCreationTime(uint64_t time) {
    
    this->creation_time = time;
    updateVersion();
    
} // end of setCreationTime method
   
/******************************************************************************//**
* @details seconds since 1904-01-01 UTC
**********************************************************************************/
void MovieHeader::setModificationTime(uint64_t time) {

    this->modification_time = time;
    updateVersion();
    
} // end of setModificationTime method

/******************************************************************************//**
* @details ticks per second
**********************************************************************************/
void MovieHeader::setTimescale(uint32_t timescale) {
    
    this->timescale = timescale;
    
} // end of setTimescale


/******************************************************************************//**
* @details ticks
**********************************************************************************/
void MovieHeader::setDuration(uint64_t duration) {
    
    this->duration = duration;
    updateVersion();
    
} // end of setDuration method

/******************************************************************************//**
*
**********************************************************************************/
uint64_t MovieHeader::getSize() const {
    
    if(version == 0) return 100;
    else             return 112;
        
} // end of getSize method

/******************************************************************************//**
*
**********************************************************************************/
void MovieHeader::read(ByteSource& source) {
    
    version = source.readUint8();
    flags = source.readBits(24);
    
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
    
    rate = source.readInt32();
    volume = source.readInt16();
    std::cout << "rate="<<rate<<std::endl;
    std::cout << "volume="<<volume<<std::endl;
    
    /*******
    * skip *
    *******/
    source.readInt16();
    source.readInt32();
    source.readInt32();
    
    for(int i=0; i<9; ++i) {
        matrix[i] = source.readInt32();
    }
    
    std::cout << "matrix:";
    for(int i=0; i<9; ++i) {
        std::cout << " "<<matrix[i];
    }
    std::cout << std::endl;
    
    /*******
    * skip *
    *******/
    for(int i=0; i<6; ++i) {
        source.readInt32();
    }
    
    next_track_id = source.readUint32();
    std::cout << "next_track: "<<next_track_id<<std::endl;
    
} // end of read method

/******************************************************************************//**
*
**********************************************************************************/
void MovieHeader::write(ByteSink& sink) const {
    
//     if(creation_time > MAX32 ||
//        modification_time > MAX32 ||
//        duration          > MAX32   ) {
//         /**********************
//         * we need the big one *
//         **********************/
//         version = 1;
//     } else {
//         /***********************
//         * the little one is OK *
//         ***********************/
//         version = 0;
//     }
    
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
    
    sink.writeInt32(rate);
    sink.writeInt16(volume);
    
    /*******
    * skip *
    *******/
    sink.writeInt16(0);
    sink.writeInt32(0);
    sink.writeInt32(0);
    
    for(int i=0; i<9; ++i) {
        sink.writeInt32(matrix[i]);
    }
    
    
    /*******
    * skip *
    *******/
    for(int i=0; i<6; ++i) {
        sink.writeInt32(0);
    }
    
    sink.writeUint32(next_track_id);


} // end of write method

/******************************************************************************//**
*
**********************************************************************************/
uint64_t MovieHeader::now() {
    
    struct timeval t;
    gettimeofday(&t, NULL);
    
    uint64_t time = t.tv_sec;
    
    time += 2082844800l; // offset between 1904 and 1970
    
    return time;

    
} // end of now method

/******************************************************************************//**
*
**********************************************************************************/
void MovieHeader::updateVersion() {
    
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
