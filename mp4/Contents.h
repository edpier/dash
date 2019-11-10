#ifndef CONTENTS_H
#define CONTENTS_H

#include "Readable.h"
#include "Type.h"

/*******************************************************************************//**
*
***********************************************************************************/
class Contents : public Readable {
    
protected:
    uint32_t size;
    Type type;
    
public:
    Contents(const std::string& type, uint32_t size);
    Contents(const Type& type, uint32_t size);
    
    Contents(const std::string& type);
    Contents(const Type& type);
    
    virtual ~Contents() {}
    
    virtual uint64_t getSize() const;
    const Type& getType() const;
    
    virtual void write(ByteSink& sink) const;
    
}; // end of Contents
#endif
