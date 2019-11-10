#ifndef SPS_H
#define SPS_H

#include "NALUContents.h"

#include <vector>

#include "BitSource.h"
    
/**************************************************************************//**
*
******************************************************************************/
class SPS : public NALUContents {
    
private:
    uint8_t profile_idc;
    uint8_t constraint_set0_flag;
    uint8_t constraint_set1_flag;
    uint8_t constraint_set2_flag;
    
    uint8_t level_idc;
    
    uint32_t seq_parameter_set_id;
    
    uint32_t max_frame_num;
    uint32_t pic_order_cnt_typ;
    
    // pic_order_cnt_typ == 0
    uint32_t max_pic_order_cnt_lsb;
    
    // pic_order_cnt_typ == 1
    bool delta_pic_order_always_zero_flag;
    int32_t offset_for_non_ref_pic;
    int32_t offset_for_top_to_bottom_field;
    //uint32_t num_ref_frames_in_pic_order_cnt_cycle
    std::vector<int32_t> offset_for_ref_frame;
    
    uint32_t num_ref_frames;
    
    bool gaps_in_frame_num_value_allowed_flag;
    
    uint32_t width;
    uint32_t height;
    
    bool frame_mbs_only_flag;
    bool mb_adaptive_frame_field_flag;
    
    bool direct_8x8_inference_flag;
    
    bool frame_cropping_flag;
    uint32_t frame_crop_left_offset;
    uint32_t frame_crop_right_offset;
    uint32_t frame_crop_top_offset;
    uint32_t frame_crop_bottom_offset;  
    
    bool vui_parameters_present_flag;
     
     
public:
    SPS();
    virtual ~SPS() {}
    
    uint32_t getWidth() const;
    uint32_t getHeight() const;
    
    virtual void read(BitSource& source);
    
    
}; // end of SPS class

#endif
