#include "MovieFragmentHeader.h"

#include "Box.h"
  
/******************************************************************************//**
*
**********************************************************************************/
MovieFragmentHeader::MovieFragmentHeader() 
                : Contents("mfhd") {
    
} // end of constructor

/******************************************************************************//**
*
**********************************************************************************/
void MovieFragmentHeader::setSequenceNumber(uint32_t sequence_number) {
    
    this->sequence_number = sequence_number;
    
} // end of setSequenceNumber method

/******************************************************************************//**
*
**********************************************************************************/
uint64_t MovieFragmentHeader::getSize() const {
    
    return 8;
    
} // end of getSize method

/******************************************************************************//**
*
**********************************************************************************/
void MovieFragmentHeader::read(ByteSource& source) {
    
    version = source.readUint8();
    flags   = source.readBits(24);
    
    std::cout <<"version="<<version<<" flags="<<flags<<std::endl;
    
    sequence_number = source.readUint32();
    std::cout << "sequence_number="<<sequence_number<<std::endl;
    
} // end if read method

/******************************************************************************//**
*
**********************************************************************************/
void MovieFragmentHeader::write(ByteSink& sink) const {
    
    sink.writeUint8(version);
    sink.writeBits(flags, 24);
    
    sink.writeUint32(sequence_number);
    
} // end of write method
