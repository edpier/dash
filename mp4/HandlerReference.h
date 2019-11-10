#ifndef HANDLER_REFERENCE_H
#define HANDLER_REFERENCE_H

#include "Contents.h"

#include "Type.h"
  
/**************************************************************************************//**
*
******************************************************************************************/
class HandlerReference : public Contents {
    
private:
    int version;
    uint32_t flags;
    
    uint32_t pre_defined;
    Type handler_typ;
    
    std::string name;
    
public:
    HandlerReference();
    virtual ~HandlerReference() {}
    
    uint64_t getSize() const;
    void read(ByteSource& source);
    void write(ByteSink& sink) const;
    
}; // end of HandlerReference class
#endif
