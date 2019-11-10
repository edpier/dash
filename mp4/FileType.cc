#include "FileType.h"

#include <iostream>

/**************************************************************************************//**
*
******************************************************************************************/
FileType::FileType() 
        : Contents("ftyp") {
    
} // end of constructor


/**************************************************************************************//**
*
******************************************************************************************/
uint64_t FileType::getSize() const {
    
    return Type::getSize()*(2+types.size());
    
} // end of getSize method

/**************************************************************************************//**
*
******************************************************************************************/
void FileType::clear() { types.clear(); }

/**************************************************************************************//**
*
******************************************************************************************/
void FileType::set(const Type& major, uint32_t minor) {
    
    this->major = major;
    this->minor = minor;
    
} // end of set method
    
/**************************************************************************************//**
*
******************************************************************************************/
void FileType::set(const std::string& major, uint32_t minor) {

    set(Type(major), minor);
    
} // end of set method

/**************************************************************************************//**
*
******************************************************************************************/
void FileType::add(const Type& type) {
    
    types.push_back(type);
    
} // end of add method

/**************************************************************************************//**
*
******************************************************************************************/
void FileType::add(const std::string& type) {
    
    add(Type(type));
    
} // end of add string method

/**************************************************************************************//**
*
******************************************************************************************/
void FileType::read(ByteSource& source) {
    
    clear();
    
    major.read(source);
    minor = source.readUint32();
    
    std::cout <<major<<"/"<<minor<<std::endl;
    
    while(source.getRemaining()>0) {
        Type type;
        type.read(source);
        types.push_back(type);
        std::cout << "    "<<type<<std::endl;
    }
    
    
} // end of read method

/**************************************************************************************//**
*
******************************************************************************************/
void FileType::write(ByteSink& sink) const {
    
    major.write(sink);
    sink.writeUint32(minor);
    
    for(Types::const_iterator it = types.begin(); it != types.end(); ++it) {
        const Type& type = *it;
        
        type.write(sink);
        
    } // end of loop over types
    
    
} // end of write method
