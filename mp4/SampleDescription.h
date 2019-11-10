#ifndef SAMPLE_DESCRIPTION_H
#define SAMPLE_DESCRIPTION_H

#include "Contents.h"

#include <vector>

#include "Container.h"

class Box;
  
/**************************************************************************//**
*
******************************************************************************/
class SampleDescription : public Contents {
    
private:
    int version;
    uint32_t flags;
    
    Container boxes;
    
public:
    SampleDescription();
    virtual ~SampleDescription() {}
    
    void clear();
    void add(Box* box);
    void add(Contents* contents);
    
    Contents* get(const std::string type, int index=0);
    
    uint64_t getSize() const;
    void read(ByteSource& source);
    void write(ByteSink& sink) const;
    
}; // end of SampleDescription class
#endif
