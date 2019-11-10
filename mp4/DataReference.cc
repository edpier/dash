#include "DataReference.h"

#include "Box.h"
  
/******************************************************************************//**
*
**********************************************************************************/
DataReference::DataReference() 
                : Contents("dref") {
                    
    version = 0;
    flags = 0;
    
} // end of constructor

/******************************************************************************//**
*
**********************************************************************************/
void DataReference::clear() {
    
    for(Boxes::iterator it = boxes.begin(); it != boxes.end(); ++it) {
        Box* box = *it;
        
        delete box;
        
    } // end of loop over boxes
    
    boxes.clear();
    
} // end of clear

/******************************************************************************//**
*
**********************************************************************************/
void DataReference::add(Box* box) {
    
    boxes.push_back(box);
    
} // end of add box method
    
/******************************************************************************//**
*
**********************************************************************************/
void DataReference::add(Contents* contents) {
    
    add(new Box(contents));
    
} // end of add contents method

/******************************************************************************//**
*
**********************************************************************************/
uint64_t DataReference::getSize() const {
    
    uint64_t size = 8;
    
    for(Boxes::const_iterator it = boxes.begin(); it != boxes.end(); ++it) {
        Box& box = **it;
        
        size += box.getSize();
        
    } // end of loop over boxes
    
    return size;
    
} // end of getSize method

/******************************************************************************//**
*
**********************************************************************************/
void DataReference::read(ByteSource& source) {

    
    version = source.readUint8();
    flags   = source.readBits(24);

    
    uint32_t entry_count = source.readUint32();
    std::cout << "entry_count="<<entry_count<<std::endl;
    
    clear();
    for(int i=0; i<(int)entry_count; ++i) {
        Box* box = new Box();
        box->read(source);
        boxes.push_back(box);
        
    } // end of loop over entries
    
} // end of read method

/******************************************************************************//**
*
**********************************************************************************/
void DataReference::write(ByteSink& sink) const {
        
    sink.writeUint8(version);
    sink.writeBits(flags, 24);

    sink.writeUint32(boxes.size());
    
    for(Boxes::const_iterator it = boxes.begin(); it != boxes.end(); ++it) {
        Box& box = **it;
        
        box.write(sink);
        
    } // end of loop over boxes
    
} // end of write method
