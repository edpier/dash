#ifndef TIME_TO_SAMPLE_H
#define TIME_TO_SAMPLE_H

#include "Contents.h"

#include <vector>

  
/**************************************************************************************//**
* table entry
******************************************************************************************/
typedef struct {
    uint32_t sample_count;
    uint32_t sample_delta;
    
} TimeToSampleEntry;

  
/**************************************************************************************//**
*
******************************************************************************************/
class TimeToSample : public Contents {
    
private:
    int version;
    uint32_t flags;
    
    typedef std::vector<TimeToSampleEntry*> Entries;
    Entries entries;
    
public:
    TimeToSample();
    virtual ~TimeToSample() {}
    
    void clear();
    void add(uint32_t sample_count, uint32_t sample_delta);

    uint64_t getSize() const;
    void read(ByteSource& source);
    void write(ByteSink& sink) const;
    
}; // end of TimeToSample class
#endif
