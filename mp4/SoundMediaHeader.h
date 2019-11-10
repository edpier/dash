#ifndef SOUND_MEDIA_HEADER_H
#define SOUND_MEDIA_HEADER_H

#include "Contents.h"

/**************************************************************************************//**
*
******************************************************************************************/
class SoundMediaHeader : public Contents {
    
private:
    int version;
    uint32_t flags;
    
    int16_t balance;
    
public:
    SoundMediaHeader();
    virtual ~SoundMediaHeader() {}
    
    uint64_t getSize() const;
    void read(ByteSource& source);
    void write(ByteSink& sink) const;
    
}; // end of SoundMediaHeader class

#endif 
