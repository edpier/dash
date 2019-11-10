#ifndef MOVIE_FRAGMENT_HEADER_H
#define MOVIE_FRAGMENT_HEADER_H

#include "Contents.h"
  
/*******************************************************************************//**
*
***********************************************************************************/
class MovieFragmentHeader : public Contents {
    
private:
    int version;
    uint32_t flags;
    
    uint32_t sequence_number;
    
public:
    MovieFragmentHeader();
    virtual ~MovieFragmentHeader() {}
    
    void setSequenceNumber(uint32_t sequence_number);
    
    uint64_t getSize() const;
    void read(ByteSource& source);
    void write(ByteSink& sink) const;
    
}; // end of MovieFragmentHeader class
#endif
