#ifndef TRACK_HEADER_H
#define TRACK_HEADER_H

#include "Contents.h"

/**************************************************************************************//**
*
******************************************************************************************/
class TrackHeader : public Contents {
    
private:
    static const uint64_t MAX32;
        
    int version;
    uint32_t flags;
    
    uint64_t creation_time;
    uint64_t modification_time;   
    uint32_t timescale;
    uint64_t duration;   
    
    int16_t layer;
    int16_t alternate_group;
    int16_t volume;
    
    int32_t matrix[9];
    
    uint32_t width;
    uint32_t height;
    
public:
    TrackHeader();
    virtual ~TrackHeader() {}
    
    void setCreationTime(uint64_t time);
    void setModificationTime(uint64_t time);
    void setTimescale(uint32_t timescale);
    void setDuration(uint64_t seconds);
    
    void setDimensions(double width, double height);
    
    uint64_t getSize() const;
    void read(ByteSource& source);
    void write(ByteSink& sink) const;
    
    static uint64_t now();
    
private:
    void updateVersion();
            
}; // end of TrackHeader class

#endif
