#include "SoundMediaHeader.h"


/**************************************************************************************//**
*
******************************************************************************************/
SoundMediaHeader::SoundMediaHeader() 
                : Contents("snhd") {
                    
    version = 0;
    flags = 0;
    
} // end of constructor

/**************************************************************************************//**
*
******************************************************************************************/
uint64_t SoundMediaHeader::getSize() const {
    
    return 6;
    
} // end of getSize method

/**************************************************************************************//**
*
******************************************************************************************/
void SoundMediaHeader::read(ByteSource& source) {
    
    version = source.readUint8();
    flags   = source.readBits(24);
    
    balance = source.readInt16();
    source.readUint16();
    
} // end of read method

/**************************************************************************************//**
*
******************************************************************************************/
void SoundMediaHeader::write(ByteSink& sink) const {
        
    sink.writeUint8(version);
    sink.writeBits(flags, 24);
    
    sink.writeInt16(balance);
    sink.writeUint16(0);
    
} // end of write method
