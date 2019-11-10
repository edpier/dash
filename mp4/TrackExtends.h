#ifndef TRACK_EXTENDS_H
#define TRACK_EXTENDS_H

#include "Contents.h"
  
/**************************************************************************************//**
*
******************************************************************************************/
class TrackExtends : public Contents {
    
private:
    int version;
    uint32_t flags;
    
    uint32_t track_ID;
    uint32_t default_sample_description_index;
    uint32_t default_sample_duration;
    uint32_t default_sample_size;
    uint32_t default_sample_flags;
    
    
public:
    TrackExtends();
    virtual ~TrackExtends() {}
    
    uint64_t getSize() const;
    void read(ByteSource& source);
    void write(ByteSink& sink) const;
    
}; // end of TrackExtends class
#endif
