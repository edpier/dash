#ifndef META_H
#define META_H

#include "Contents.h"

#include <vector>

class Box;
  
/**************************************************************************************//**
*
******************************************************************************************/
class Meta : public Contents {
    
private:
    int version;
    uint32_t flags;
    
    typedef std::vector<Box*> Boxes;
    Boxes boxes;
    
    
public:
    Meta();
    virtual ~Meta() {}
    
    uint64_t getSize() const;
    void read(ByteSource& source);
    
}; // end of Meta class
#endif
