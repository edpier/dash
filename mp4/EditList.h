#ifndef EDIT_LIST_H
#define EDIT_LIST_H

#include "Contents.h"
  
/**************************************************************************************//**
*
******************************************************************************************/
class EditList : public Contents {
    
private:
    int version;
    uint32_t flags;
    
    uint32_t entry_count;
    
    
public:
    EditList(uint32_t size);
    virtual ~EditList() {}
    
    void read(ByteSource& source);
    
}; // end of EditList class
#endif
