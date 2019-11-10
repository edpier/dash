#ifndef NALU_CONTENTS_H
#define NALU_CONTENTS_H

#include "BitSource.h"
    
/**************************************************************************//**
*
******************************************************************************/
class NALUContents {
    
private:
    
public:
    NALUContents();
    virtual ~NALUContents() {}
    
    virtual void read(BitSource& source)=0;
    
    
}; // end of NALUContents class

#endif
