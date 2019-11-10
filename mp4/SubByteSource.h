#ifndef SUB_BYTE_SOURCE_H
#define SUB_BYTE_SOURCE_H

#include "ByteSource.h"

#include <string>

/******************************************************************************//**
*
**********************************************************************************/
class SubByteSource : public ByteSource {
    
private:
    std::string name;
    ByteSource& source;
    uint64_t remaining;
    
public:
    SubByteSource(const std::string& name, ByteSource& source, uint64_t length);
    virtual ~SubByteSource() {}
    
    bool hasMoreData() const;
    uint64_t getRemaining() const;
    virtual void read(unsigned char* data, int length);
    
}; // end of SubByteSource class

#endif
