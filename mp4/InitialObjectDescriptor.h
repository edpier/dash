#ifndef INITIAL_OBJECT_DESCRIPTOR_H
#define INITIAL_OBJECT_DESCRIPTOR_H

#include "Contents.h"

/**************************************************************************//**
*
******************************************************************************/
class InitialObjectDescriptor : public Contents {
    
private:
    int version;
    uint32_t flags;
    
    uint8_t file_iod_type_tag;
    uint8_t extended_descriptor_type_tag_string1;
    uint8_t extended_descriptor_type_tag_string2;
    uint8_t extended_descriptor_type_tag_string3;
    uint8_t descriptor_type_length;
    
    uint16_t od_id;
    uint8_t od_profile_level;
    uint8_t scene_profile_level;   
    uint8_t audio_profile_level;   
    uint8_t video_profile_level;
    uint8_t graphics_profile_level;
    uint8_t es_id_included_descriptor_type_tag;

    uint8_t another_extended_descriptor_type_tag_string1;
    uint8_t another_extended_descriptor_type_tag_string2;
    uint8_t another_extended_descriptor_type_tag_string3;
    uint8_t another_descriptor_type_length;
    
    uint32_t track_id;

public:
    InitialObjectDescriptor();
    virtual ~InitialObjectDescriptor() {}
    
    uint64_t getSize() const;
    void read(ByteSource& source);
    void write(ByteSink& sink) const;
    
}; // end of InitialObjectDescriptor
#endif
