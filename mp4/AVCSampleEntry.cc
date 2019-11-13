#include "AVCSampleEntry.h"

#include "Box.h"

/**************************************************************************//**
*
******************************************************************************/
AVCSampleEntry::AVCSampleEntry() 
              : Contents("avc1") {
                  
    config = new Box();
    extensions = NULL;
    
    data_reference_index = 1;
    
    width  = 0;
    height = 0;
    
    horizresolution = 0x00480000; // 72 dpi
     vertresolution = 0x00480000;
     
    frame_count = 1;
    
    depth = 0x18; // color, no alpha
    
    
} // end of constructor
  
/**************************************************************************//**
*
******************************************************************************/
AVCSampleEntry::~AVCSampleEntry() {

      delete config;
      
} // end of destructor
      
/**************************************************************************//**
*
******************************************************************************/
void AVCSampleEntry::setDimensions(uint16_t width, uint16_t height) {
    
    this->width  = width;
    this->height = height;
    
} // end of setDimensions
      
/**************************************************************************//**
*
******************************************************************************/
Contents* AVCSampleEntry::getConfig() { 
    
    if(config == NULL) return NULL;
    else return config->getContents();
    
} // end of getConfig method

/**************************************************************************//**
*
******************************************************************************/
void AVCSampleEntry::setConfig(Contents* config) {
    
    this->config->setContents(config);
    
} // end of setConfig method
      
      
/**************************************************************************//**
*
******************************************************************************/
uint64_t AVCSampleEntry::getSize() const {
    
    
    uint64_t size =  78 + config->getSize();
    if(extensions != NULL) size += extensions->getSize();
    
    return size;

    
} // end of getSize method
  
/**************************************************************************//**
*
******************************************************************************/
void AVCSampleEntry::read(ByteSource& source) {
    
    source.readUint32(); // reserved
    source.readUint16();
    
    data_reference_index = source.readUint16();
    std::cout << "data_reference_index="<<data_reference_index<<std::endl;
    
    source.readUint16();
    source.readUint16();
    source.readUint32();
    source.readUint32();
    source.readUint32();
    
    width  = source.readUint16();
    height = source.readUint16();
    
    std::cout <<" width="<<width<<" height="<<height<<std::endl;
    
    horizresolution = source.readUint32();
    vertresolution  = source.readUint32();
    
    source.readUint32();
    
    frame_count = source.readUint16();
    std::cout << "frame_count = "<<frame_count<<std::endl;
    
    /******************
    * compressor name *
    ******************/
    uint8_t size = source.readUint8();
    if(size>31) size = 31;
    source.readString(compressorname, size);
    
    for(int i=size; i<31; ++i) {
        source.readUint8();
    }
    std::cout << "compressorname=|"<<compressorname<<"|"<<std::endl;
    
    depth = source.readUint16();
    std::cout << "depth="<<depth<<std::endl;
    
    int16_t tmp = source.readInt16(); // -1
    std::cout << "tmp="<<tmp<<std::endl;
    
    config->read(source);
    std::cout << "done reading config"<<std::endl;
    
    if(source.getRemaining()>0) {
        extensions = new Box();
        extensions->read(source);
    }

        
} // end of read method
  
/**************************************************************************//**
*
******************************************************************************/
void AVCSampleEntry::write(ByteSink& sink) const {
    
    /********************************
    * sample entry 6 bytes reserved *
    ********************************/
    sink.writeUint32(0);
    sink.writeUint16(0);
    
    sink.writeUint16(data_reference_index);
    
    /**********************
    * visual sample entry *
    **********************/
    sink.writeUint16(0); // reserved and predefined
    sink.writeUint16(0);
    sink.writeUint32(0);
    sink.writeUint32(0);
    sink.writeUint32(0);
    
    sink.writeUint16(width);
    sink.writeUint16(height);
    
    sink.writeUint32(horizresolution);
    sink.writeUint32( vertresolution);
    
    sink.writeUint32(0);
    
    sink.writeUint16(frame_count);

    uint8_t size = compressorname.length();
    if(size>30) size = 30;
    sink.writeUint8(size);
    sink.writeString(compressorname.substr(0, 30)); // leave room for null terminator
    
    /******************************************************************
    * pad out to 32 bytes. Note write String writes a null terminator
    * so we start at size+1 to account for it
    ******************************************************************/
    for(int i=size+1; i<31; ++i) {
        sink.writeUint8(0);
    }

    sink.writeUint16(depth);

    sink.writeInt16(-1);

    config->write(sink);
    if(extensions != NULL) extensions->write(sink);

} // end of write method
