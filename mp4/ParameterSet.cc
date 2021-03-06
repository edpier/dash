#include "ParameterSet.h"

#include "ArrayByteSource.h"
#include "NALU.h"
  
/**************************************************************************//**
*
******************************************************************************/
ParameterSet::ParameterSet() {
    
    size = 0;
    data = NULL;
    
} // end of constructor
  
/**************************************************************************//**
*
******************************************************************************/
ParameterSet::~ParameterSet() {
    
    delete [] data;
    
} // end of destructor
  
/**************************************************************************//**
*
******************************************************************************/
void ParameterSet::setSize(uint16_t size) {
    
    std::cout << "parameter set size="<<size<<std::endl;
    
    this->size = size;
    data = new uint8_t[size];
    
} // end of setSize method
  
/**************************************************************************//**
*
******************************************************************************/
uint8_t* ParameterSet::getData() { return data; }
      
/**************************************************************************//**
*
******************************************************************************/
const uint8_t* ParameterSet::getData() const { return data; }
  
/**************************************************************************//**
*
******************************************************************************/
uint64_t ParameterSet::getSize() const { return size; }
  
/**************************************************************************//**
*
******************************************************************************/
void ParameterSet::read(ByteSource& source) {
    
    setSize(source.readUint16());
    
    source.read(data, size);
    
    NALU nalu;
    ArrayByteSource as(data, size);
    nalu.read(as);
    
    
    
    
} // end of read method
  
/**************************************************************************//**
*
******************************************************************************/
void ParameterSet::write(ByteSink& sink) const {
    
    sink.writeUint16(size);
    
    for(int i=0; i<size; ++i) {
        sink.writeUint8(data[i]);
    }
    
} // end of write method
