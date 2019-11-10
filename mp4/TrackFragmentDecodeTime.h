#ifndef TRACK_FRAGMENT_DECODE_TIME_H
#define TRACK_FRAGMENT_DECODE_TIME_H

#include "Contents.h"

#include <vector>


  
/******************************************************************************//**
*
**********************************************************************************/
class TrackFragmentDecodeTime : public Contents {
    
private:
    int version;
    uint32_t flags;
    
    uint64_t base_media_decode_time;
    
public:
    TrackFragmentDecodeTime();
    virtual ~TrackFragmentDecodeTime() {}
    
    void setBaseMediaDecodeTime(uint64_t time);
       
    uint64_t getSize() const; 
    void read(ByteSource& source);
    void write(ByteSink& sink) const;
    
}; // end of TrackFragmentDecodeTime class
#endif
