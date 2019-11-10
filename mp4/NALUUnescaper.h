#ifndef NALU_UNESCAPER_H
#define NALU_UNESCAPER_H

#include "ByteSource.h"

#include <cstdint>
#include <string>

/**************************************************************************//**
*
******************************************************************************/
class NALUUnescaper : public ByteSource {
    
private:
    ByteSource& source;
    
    int nzeros;
    
public:
    NALUUnescaper(ByteSource& source);
    virtual ~NALUUnescaper() {}
    
    virtual void read(unsigned char* data, int length);
        

}; // end of NALUUnescaper class

#endif
