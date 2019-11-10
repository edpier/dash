#ifndef CONTAINER_H
#define CONTAINER_H

#include "Contents.h"

#include <vector>

#include "Box.h"

/*******************************************************************************//**
*
***********************************************************************************/
class Container : public Contents {
    
private:
    typedef std::vector<Box*> Boxes;
    Boxes boxes;
    
public:
    Container(const Type type);
    Container(const std::string& type);
    virtual ~Container();
    
    void clear();
    void add(Box* box);
    void add(Contents* contents);
    
    Contents* get(const std::string& type, int index=0);
    int getBoxCount() const;
    
    uint64_t getSize() const;
    void read(ByteSource& source);
    void write(ByteSink& sink) const;
    
private:
    Contents* get(const std::string& type, int index, int& count);
    
}; // end of Container class

#endif
