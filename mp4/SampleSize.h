#ifndef SAMPLE_SIZE_H
#define SAMPLE_SIZE_H

#include "Contents.h"

#include <vector>
  
/**************************************************************************************//**
*
******************************************************************************************/
class SampleSize : public Contents {
    
private:
    int version;
    uint32_t flags;
    
    uint32_t sample_size;
    
    typedef std::vector<uint32_t> Entries;
    Entries entries;

    
public:
    SampleSize();
    virtual ~SampleSize() {}
       
    void clear();
    void add(uint32_t entry_size);

    uint64_t getSize() const; 
    void read(ByteSource& source);
    void write(ByteSink& sink) const;
    
}; // end of SampleSize class
#endif
