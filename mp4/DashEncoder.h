#ifndef DASH_ENCODER_H
#define DASH_ENCODER_H

#include <stdint.h>

#include "AVCConfiguration.h"
#include "Container.h"

/************************************************************************//**
*
****************************************************************************/
class DashEncoder {
    
private:
    Container init;
    
    uint32_t fragment_count;
    Container* fragment;
    
public:
    DashEncoder();
    virtual ~DashEncoder() {}
    
    void addNALU(uint8_t* data, int size);
    
private:
    void createInit(uint32_t width, uint32_t height);
    void createFragment();
    void writeFragment();
    void addFrame(uint8_t* data, int size);
    
    AVCConfiguration* getAVCConfiguration();
    
}; // end of DashEncoder class

#endif
