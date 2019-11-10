#ifndef SEGMENT_TYPE_H
#define SEGMENT_TYPE_H

#include "Contents.h"

#include <vector>

#include "Type.h"

/**************************************************************************************//**
*
******************************************************************************************/
class SegmentType : public Contents {
    
private:
    Type major;
    uint32_t minor;
    
    typedef std::vector<Type> Types;
    Types types;
    
public:
    SegmentType();
    virtual ~SegmentType() {}
    
    uint64_t getSize() const;
    void clear();
    
    void set(const Type& major, uint32_t minor);
    void set(const std::string& major, uint32_t minor);
    void add(const Type& type);
    void add(const std::string& type);
    
    void read(ByteSource& source);
    void write(ByteSink& sink) const;
    
}; // end of SegmentType class

#endif
