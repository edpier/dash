#include "SampleDescription.h"

#include "Box.h"
  
/**************************************************************************//**
*
******************************************************************************/
SampleDescription::SampleDescription() 
                : Contents("stsd"),
                  boxes("    ") {
    
} // end of constructor

/**************************************************************************//**
*
******************************************************************************/
void SampleDescription::clear() {
    
    boxes.clear();
    
} // end of clear method

/**************************************************************************//**
*
******************************************************************************/
void SampleDescription::add(Box* box) {
    
    boxes.add(box);
    
} // end of add box method

/**************************************************************************//**
*
******************************************************************************/
void SampleDescription::add(Contents* contents) {
    
    add(new Box(contents));
    
} // end of add contents method

/**************************************************************************//**
*
******************************************************************************/
Contents* SampleDescription::get(const std::string type, int index) {
    
    return boxes.get(type, index);
    
} // end of getContents method


/**************************************************************************//**
*
******************************************************************************/
uint64_t SampleDescription::getSize() const {
    
    return  8 + boxes.getSize();

} // end of getSize method
    


/**************************************************************************//**
*
******************************************************************************/
void SampleDescription::read(ByteSource& source) {

    version = source.readUint8();
    flags   = source.readBits(24);
    
    std::cout <<"version="<<version<<" flags="<<flags<<std::endl;

    
    uint32_t entry_count = source.readUint32();
    std::cout << "entry_count="<<entry_count<<std::endl;
    
    for(int i=0; i<(int)entry_count; ++i) {
        std::cout << "reading entry "<<i<<std::endl;
        Box* box = new Box();
        box->read(source);
        boxes.add(box);

        std::cout << "done reading entry"<<std::endl;
        
    } // end of loop over entries


    
} // end of read method

/**************************************************************************//**
*
******************************************************************************/
void SampleDescription::write(ByteSink& sink) const {

    sink.writeUint8(version);
    sink.writeBits(flags, 24);

    sink.writeUint32(boxes.getBoxCount());
    boxes.write(sink);
  
    
} // end of write method
