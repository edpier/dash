#ifndef TRACK_FRAGMENT_HEADER_H
#define TRACK_FRAGMENT_HEADER_H

#include "Contents.h"
  
/**************************************************************************************//**
*
******************************************************************************************/
class TrackFragmentHeader : public Contents {
    
private:
    int version;
    uint32_t flags;
    
    uint32_t track_ID;
    
// all the following are optional fields
    uint64_t base_data_offset;
    uint32_t sample_description_index;
    uint32_t default_sample_duration;
    uint32_t default_sample_size;
    uint32_t default_sample_flags;
    
    
public:
    TrackFragmentHeader();
    virtual ~TrackFragmentHeader() {}
    
    void setTrackID(uint32_t track_id);
    
    void setBaseDataOffset(uint64_t base_data_offset);
    void setSampleDescriptionIndex(uint32_t sample_description_index);
    void setDefaultSampleDuration(uint32_t default_sample_duration);
    void setDefaultSampleSize(uint32_t default_sample_size);
    void setDefaultSampleFlags(uint32_t default_sample_flags);
    
    uint64_t getSize() const;
    void read(ByteSource& source);
    void write(ByteSink& sink) const;
    
}; // end of TrackFragmentHeader class
#endif
