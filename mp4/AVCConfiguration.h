#ifndef AVC_CONFIGURATION_H
#define AVC_CONFIGURATION_H

#include "Contents.h"

#include <vector>

#include "ParameterSet.h"
  
/**************************************************************************//**
*
******************************************************************************/
class AVCConfiguration : public Contents {
    
private:

    uint8_t configurationVersion;
    uint8_t AVCProfileIndication;
    uint8_t profileCompatibility;
    uint8_t AVCLevelIndication;
    
    uint8_t length_size;
    
    typedef std::vector<ParameterSet*> ParameterSets;
    ParameterSets spses;
    ParameterSets ppses;
    
    uint8_t chroma_format;
    uint8_t bit_depth_luma;
    uint8_t bit_depth_chroma;

    
public:
    AVCConfiguration();
    virtual ~AVCConfiguration();
    
    uint8_t getLengthSize() const;
    
    void addSPS(uint8_t* data, int size);
    void addPPS(uint8_t* data, int size);
    
    uint64_t getSize() const;
    void read(ByteSource& source);
    void write(ByteSink& sink) const;
    
}; // end of AVCConfigurationclass
#endif
