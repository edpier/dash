#include "HandlerReference.h"
  
/**************************************************************************************//**
*
******************************************************************************************/
HandlerReference::HandlerReference() 
                : Contents("hdlr"),
                  handler_typ("vide") {
                    
    version = 0;
    flags =0;
    
    pre_defined = 0;
    
} // end of constructor

/**************************************************************************************//**
*
******************************************************************************************/
uint64_t HandlerReference::getSize() const {
    
    return 24 + name.length()+1;
    
} // end of getSize method

/**************************************************************************************//**
*
******************************************************************************************/
void HandlerReference::read(ByteSource& source) {
    
    version = source.readUint8();
    flags   = source.readBits(24);
    
    pre_defined = source.readUint32();
    //source.readUint32();
    handler_typ.read(source);
    std::cout <<"handler_type="<<handler_typ<<std::endl;
    
    source.readUint32();
    source.readUint32();
    source.readUint32();
    
    source.readString(name);
    std::cout << "name="<<name<<std::endl;
    
} // end of read method

/**************************************************************************************//**
*
******************************************************************************************/
void HandlerReference::write(ByteSink& sink) const {
    
    sink.writeUint8(version);
    sink.writeBits(flags, 24);
    
    sink.writeUint32(pre_defined);

    handler_typ.write(sink);
 
    sink.writeUint32(0);
    sink.writeUint32(0);
    sink.writeUint32(0);
    
    sink.writeString(name);
    
} // end of read method
