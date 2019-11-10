#ifndef TRACK_FRAGMENT_RUN_H
#define TRACK_FRAGMENT_RUN_H

#include "Contents.h"

#include <vector>
  
/******************************************************************************//**
*
**********************************************************************************/
typedef struct {
    
    uint32_t sample_duration;
    uint32_t sample_size;
    uint32_t sample_flags;
    uint32_t sample_composition_time_offset;
    
} TFREntry;
  
/******************************************************************************//**
*
**********************************************************************************/
class TrackFragmentRun : public Contents {
    
private:
    int version;
    uint32_t flags;
    
    int32_t data_offset;
    uint32_t first_sample_flags;

    typedef std::vector<TFREntry*> Entries;
    Entries entries;
    
    
public:
    TrackFragmentRun();
    virtual ~TrackFragmentRun();
    
    void clear();
    
    void setDataOffset(int32_t data_offset);
    void setFirstSampleFlags(uint32_t first_sample_flags);
    
    void add();
    
    void setSampleDuration(uint32_t sample_duration);
    void setSampleSize(uint32_t sample_size);
    void setSampleFlags(uint32_t sample_flags);
    void setSampleCompositionTimeOffset(uint32_t sample_composition_time_offset);
    
    uint64_t getSize() const;
    void read(ByteSource& source);
    void write(ByteSink& sink) const;
    
}; // end of TrackFragmentRun class
#endif
