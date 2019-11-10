#ifndef MOVIE_HEADER_H
#define MOVIE_HEADER_H

#include "Contents.h"

#include <cstdint>

/**************************************************************************************//**
*
******************************************************************************************/
class MovieHeader : public Contents {
    
private:
    static const uint64_t MAX32;
    
    int version;
    uint32_t flags;
    
    uint64_t creation_time;
    uint64_t modification_time;   
    uint32_t timescale;
    uint64_t duration;
    
    uint32_t rate;
    int16_t volume;
    
    int32_t matrix[9];
    
    uint32_t next_track_id;
    
public:
    MovieHeader();
    virtual ~MovieHeader() {}
    
    void setCreationTime(uint64_t time);
    void setModificationTime(uint64_t time);
    void setTimescale(uint32_t timescale);
    void setDuration(uint64_t seconds);
    
    uint64_t getSize() const;
    void read(ByteSource& source);
    void write(ByteSink& sink) const;
    
    static uint64_t now();
    
private:
    void updateVersion();
    
}; // end of MovieHeader class
#endif
