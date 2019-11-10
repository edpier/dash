#ifndef AVC_SAMPLE_ENTRY_H
#define AVC_SAMPLE_ENTRY_H

#include "Contents.h"

#include <vector>

class Box;
  
/**************************************************************************//**
*
******************************************************************************/
class AVCSampleEntry : public Contents {
    
private:
    int version;
    uint32_t flags;
    
    uint16_t data_reference_index;
    
    uint16_t width;
    uint16_t height;
    
    uint32_t horizresolution; // fixed point 16.16
    uint32_t vertresolution;
    
    uint16_t frame_count; // frames per sample
    std::string compressorname;
    
    uint16_t depth;
    
    Box* config;
    Box* extensions;


    
public:
    AVCSampleEntry();
    virtual ~AVCSampleEntry();
    
    void setDimensions(uint16_t width, uint16_t height);
    
    Contents* getConfig();
    void setConfig(Contents* config);
    
    uint64_t getSize() const;
    void read(ByteSource& source);
    void write(ByteSink& sink) const;
    
}; // end of AVCSampleEntryclass
#endif
