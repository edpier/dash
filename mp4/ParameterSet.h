#ifndef PARAMETER_SET_H
#define PARAMETER_SET_H

#include "Contents.h"

#include <vector>
  
/**************************************************************************//**
*
******************************************************************************/
class ParameterSet {
    
private:
    
    uint16_t size;
    uint8_t* data;

public:
    ParameterSet();
    virtual ~ParameterSet();
    
    void setSize(uint16_t size);
    uint8_t* getData();
    const uint8_t* getData() const;
    
    uint64_t getSize() const;
    void read(ByteSource& source);
    void write(ByteSink& sink) const;
    
}; // end of AVCConfigurationclass
#endif
