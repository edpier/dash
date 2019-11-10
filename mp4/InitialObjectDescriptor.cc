#include "InitialObjectDescriptor.h"

/**************************************************************************//**
*
******************************************************************************/
InitialObjectDescriptor::InitialObjectDescriptor() 
                       : Contents("iods") {
}



/**************************************************************************//**
*
******************************************************************************/
uint64_t InitialObjectDescriptor::getSize() const {
    
    return 0;
    
} // end of getSize method

/**************************************************************************//**
*
******************************************************************************/
void InitialObjectDescriptor::read(ByteSource& source) {
    
    version = source.readUint8();
    flags   = source.readBits(24);
    
    file_iod_type_tag = source.readUint8();
    std::cout << "file_iod_type_tag="<<(int)file_iod_type_tag<<std::endl;
    
    
    descriptor_type_length = source.readUint8();
    
    std::cout << "descriptor_type_length="<<(int)descriptor_type_length<<std::endl;
    
    od_id = source.readUint16();
    od_profile_level = source.readUint8();
    scene_profile_level = source.readUint8();   
    audio_profile_level = source.readUint8();   
    video_profile_level = source.readUint8();
    graphics_profile_level = source.readUint8();
    
    std::cout << "profiles "<<(int)od_profile_level<<" "
              << (int)scene_profile_level<<" "
              << (int)audio_profile_level<<" "
              << (int)video_profile_level<<" "
              << (int)graphics_profile_level<<std::endl;
    
    
    
} // end of read method

/**************************************************************************//**
*
******************************************************************************/
void InitialObjectDescriptor::write(ByteSink& sink) const {
    
} // end of write method
