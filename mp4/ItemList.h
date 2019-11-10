#ifndef ITEM_LIST_H
#define ITEM_LIST_H

#include "Contents.h"

#include <vector>

class Box;
  
/**************************************************************************************//**
*
******************************************************************************************/
typedef struct {
    
    Type tag_name;
    uint32_t npayload;
    uint32_t data_typ;
    uint8_t* payload;
    
} TagRecord;

  
/**************************************************************************************//**
*
******************************************************************************************/
class ItemList : public Contents {
    
private:
    int version;
    uint32_t flags;
    
    typedef std::vector<TagRecord*> Tags;
    Tags tags;
    
    
public:
    ItemList();
    virtual ~ItemList() {}
    
    uint64_t getSize() const;
    void read(ByteSource& source);
    
}; // end of ItemList class
#endif
