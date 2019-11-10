#ifndef READABLE_H
#define READABLE_H

#include "ByteSource.h"

/**************************************************************************************//**
*
******************************************************************************************/
class Readable {
    
public:
    virtual void read(ByteSource& source) =0;
    
}; // end of Readable

#endif
