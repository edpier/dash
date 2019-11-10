#ifndef VIDEO_MEDIA_HEADER_H
#define VIDEO_MEDIA_HEADER_H

#include "Contents.h"
  
/**************************************************************************************//**
*
******************************************************************************************/
class VideoMediaHeader : public Contents {
    
private:
    int version;
    uint32_t flags;
    
    uint32_t entry_count;
    
    uint16_t graphics_mode;
    uint16_t opcolor_r;
    uint16_t opcolor_g;
    uint16_t opcolor_b;
    
public:
    VideoMediaHeader();
    virtual ~VideoMediaHeader() {}
    
    uint64_t getSize() const;
    void read(ByteSource& source);
    void write(ByteSink& sink) const;
    
}; // end of VideoMediaHeader class
#endif
