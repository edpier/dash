#ifndef NALU_H
#define NALU_H

#include "ByteSource.h"

class NALUContents;
    
/**************************************************************************//**
*
******************************************************************************/
class NALU {
    
private:
    int nal_ref_idc;
    int nal_unit_typ;
    
    NALUContents* contents;

public:
    NALU();
    virtual ~NALU();
    
    NALUContents* getContents();
    
    void read(ByteSource& source);
    
    
}; // end of NALU class

#endif
