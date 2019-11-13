#ifndef SAMPLE_TABLE_H
#define SAMPLE_TABLE_H

#include "Contents.h"

/**************************************************************************//**
* @brief The offset between decoding and composition time
******************************************************************************/
class SampleTable : public Contents {
    
private:
    int version;
    uint32_t flags;
    
public:
    SampleTable();
    virtual ~SampleTable();
    
    uint64_t getSize() const;
    void read(ByteSource& source);
    void write(ByteSink& sink) const;
    
}; // end of SampleTable class


#endif
