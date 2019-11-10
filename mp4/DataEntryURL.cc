#include "DataEntryURL.h"
  
/******************************************************************************//**
*
**********************************************************************************/
DataEntryURL::DataEntryURL() 
                : Contents("url ") {
                    
    version = 0;
    
    set("");
    
} // end of constructor

/******************************************************************************//**
*
**********************************************************************************/
void DataEntryURL::set(const std::string& url) {
    
    if(url.length() == 0) flags = 1;
    else                  flags = 0;
    
    this->url = url;
    
} // end of set method


/******************************************************************************//**
*
**********************************************************************************/
uint64_t DataEntryURL::getSize() const {
    
    if(flags&1) return 4;
    else        return 4 + url.length()+1;
    
} // end of getSize method

/******************************************************************************//**
*
**********************************************************************************/
void DataEntryURL::read(ByteSource& source) {
        
    std::cout << "reading url"<<std::endl;
    
    version = source.readUint8();
    flags   = source.readBits(24);
    
        
    std::cout << "version="<<version<<std::endl;
    std::cout << "flags="<<flags<<std::endl;
    
    if((flags & 1) == 0) {
        source.readString(url);
        std::cout << url<<std::endl;
    }
    
    
    
} // end of read method

/******************************************************************************//**
*
**********************************************************************************/
void DataEntryURL::write(ByteSink& sink) const {

    sink.writeUint8(version);
    sink.writeBits(flags, 24);
    
    if((flags & 1) == 0) {
        sink.writeString(url);
    }
    
    
} // end of read method
