#include "Meta.h"

#include "Box.h"
  
/**************************************************************************************//**
*
******************************************************************************************/
Meta::Meta() 
    : Contents("meta") {
    
} // end of constructor

/**************************************************************************************//**
*
******************************************************************************************/
uint64_t Meta::getSize() const {
    
    int size = 4;
    for(Boxes::const_iterator it = boxes.begin(); it != boxes.end(); ++it) {
        Box& box = **it;
        
        size += box.getSize();
        
    } // end of loop over boxes
    
    return size;
    
} // end of getSize method

/**************************************************************************************//**
*
******************************************************************************************/
void Meta::read(ByteSource& source) {
    
    version = source.readUint8();
    flags   = source.readBits(24);
    
    std::cout <<"version="<<version<<" flags="<<flags<<std::endl;
    
    while(source.getRemaining()>0) {
        Box* box = new Box();
        box->read(source);
        boxes.push_back(box);
    }
    
} // end if read method
