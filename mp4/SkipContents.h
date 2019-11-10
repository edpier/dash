#ifndef SKIP_CONTENTS_H
#define SKIP_CONTENTS_H

#include "Contents.h"

/*****************************************************************************//**
*
*********************************************************************************/
class SkipContents : public Contents {
    
private:
    uint8_t* data;
    int nbytes;
    
public:
    SkipContents(const Type& type, uint32_t size);
    virtual ~SkipContents();
    
    int getByteCount() const;
          uint8_t* getBytes();
    const uint8_t* getBytes() const;
    
    void read(ByteSource& source);
    
}; // end of SkipContents class

#endif
