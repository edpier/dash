#ifndef DATA_REFERENCE_H
#define DATA_REFERENCE_H

#include "Contents.h"

#include <vector>

class Box;
  
/**************************************************************************************//**
*
******************************************************************************************/
class DataReference : public Contents {
    
private:
    int version;
    uint32_t flags;
    
    typedef std::vector<Box*> Boxes;
    Boxes boxes;

    
public:
    DataReference();
    virtual ~DataReference() {}
    
    void clear();
    void add(Box* box);
    void add(Contents* contents);
    
    uint64_t getSize() const;
    void read(ByteSource& source);
    void write(ByteSink& sink) const;
    
}; // end of DataReference class
#endif
