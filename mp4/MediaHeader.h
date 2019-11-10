#ifndef MEDIA_HEADER_H
#define MEDIA_HEADER_H

#include "Contents.h"
  
/**************************************************************************************//**
*
******************************************************************************************/
class MediaHeader : public Contents {
    
private:
    static const uint64_t MAX32;
    
    int version;
    uint32_t flags;
    
    uint64_t creation_time;
    uint64_t modification_time;   
    uint32_t timescale;
    uint64_t duration;   
    
    uint8_t languages[3];
    
public:
    MediaHeader();
    virtual ~MediaHeader() {}
    
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
    
}; // end of MediaHeader class

#endif
