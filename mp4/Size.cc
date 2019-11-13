#include "Size.h"

#include "Type.h"

const uint64_t Size::MAX32 = 0xffffffff;

/*********************************************************************//**
*
*************************************************************************/
Size::Size() {
    
    size = 0;

} // end of default constructor

/*********************************************************************//**
*
*************************************************************************/
Size::Size(uint64_t size) {
    
    this->size = size;
    
} // end of constructor

/*********************************************************************//**
*
*************************************************************************/
Size::Size(const Size& size) {
    
    this->size = size.size;
    
} // end of copy constructor

/*********************************************************************//**
* @brief add the size of the type and this size field
*************************************************************************/
void Size::addHeader() {
    
    size += Type::getSize();
    size += 4; // the small size size
    
    if(size > MAX32) size += 8; // needs to be a big size
    
} // end of addHeader method


/*********************************************************************//**
*
*************************************************************************/
uint64_t Size::getValue() { return size; }

/*********************************************************************//**
*
*************************************************************************/
int Size::getSize() {
    
    if(size<=MAX32) return  4;
    else            return 12;
    
} // end of getSize method

/*********************************************************************//**
*
*************************************************************************/
void Size::read(ByteSource& source) {
    
    size = source.readUint32();
    if(size == 1) {
        size = source.readUint64();
    }
        
} // end of read method

/*********************************************************************//**
*
*************************************************************************/
void Size::write(ByteSink& sink) {
    
    if(size<=MAX32) {
        /********
        * small *
        ********/
        sink.writeUint32(size);
    } else {
        /******
        * big *
        ******/
        sink.writeUint32(1);
        sink.writeUint64(size);
    }
    
} // end of write method

/*********************************************************************//**
*
*************************************************************************/
const Size& Size::operator=(uint64_t size) {
    
    this->size = size;
    return *this;
    
} // end of assignment operator

/*********************************************************************//**
*
*************************************************************************/
const Size& Size::operator=(const Size& size) {
    
    this->size = size.size;
    return *this;
    
} // end of assignent operator

/*********************************************************************//**
*
*************************************************************************/
Size::operator uint64_t() const {
    
    return size;
    
} // end of uint64_t converter

/*********************************************************************//**
*
*************************************************************************/
std::ostream& operator<<(std::ostream& out, const Size& size) {
    
    out << size.size;
    return out;
    
} // end of print operator
