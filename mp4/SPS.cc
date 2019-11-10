#include "SPS.h"

#include <iostream>
    
/**************************************************************************//**
*
******************************************************************************/
SPS::SPS() {

} // end of constructor
    
/**************************************************************************//**
*
******************************************************************************/
uint32_t SPS::getWidth() const { 
    
    return width - frame_crop_left_offset - frame_crop_right_offset; 
}
        
/**************************************************************************//**
*
******************************************************************************/
uint32_t SPS::getHeight() const { 
    
    return height - frame_crop_top_offset - frame_crop_bottom_offset; 
}
    
/**************************************************************************//**
*
******************************************************************************/
void SPS::read(BitSource& source) {
    
    profile_idc = source.readU(8);
    std::cout << "NALU profile_idc="<<(int)profile_idc<<std::endl;
    
    constraint_set0_flag = source.readU(1);
    constraint_set1_flag = source.readU(1);
    constraint_set2_flag = source.readU(1);
    
    source.readU(5); // reserved
    
    std::cout <<" flags="<<(int)constraint_set0_flag<<" "
                         <<(int)constraint_set1_flag<<" "
                         <<(int)constraint_set2_flag<<std::endl;
    
    level_idc = source.readU(8);
    std::cout << "NALU level_idc="<<(int)level_idc<<std::endl;
    
    seq_parameter_set_id = source.readUE();
    std::cout << "seq_parameter_set_id="<<seq_parameter_set_id<<std::endl;
    
    uint32_t tmp = source.readUE();
    max_frame_num = 1<<(tmp+4);
    std::cout <<"log2 max frame num minus 4 = "<<tmp<<std::endl;
    std::cout << "max frame num="<<max_frame_num<<std::endl;
    std::cout << std::endl;
    
    pic_order_cnt_typ = source.readUE();
    std::cout << "pic_order_cnt_type="<<pic_order_cnt_typ<<std::endl;
    
    if(pic_order_cnt_typ == 0) {
        /*********
        * type 0 *
        *********/
        tmp = source.readUE();
        max_pic_order_cnt_lsb = 1 << (tmp+4);
        std::cout << "tmp="<<tmp<<std::endl;
        std::cout << "max_pic_order_cnt_lsb="<<max_pic_order_cnt_lsb<<std::endl;
        
        std::cout << "bogus: "<<source.readUE()<<std::endl;
        std::cout << "bogus: "<<source.readUE()<<std::endl;
        
    } else if(pic_order_cnt_typ == 1) {
        /*********
        * type 1 *
        *********/
        delta_pic_order_always_zero_flag = (source.readU(1) == 1);
        offset_for_non_ref_pic         = source.readSE();
        offset_for_top_to_bottom_field = source.readSE();
        
        uint32_t n = source.readUE();
        std::cout << "number of offsets = "<<n<<std::endl;
        offset_for_ref_frame.clear();
        for(uint32_t i = 0; i<n; ++i) {
            offset_for_ref_frame.push_back(source.readSE());
        }
    }
    std::cout << std::endl;
    
    num_ref_frames = source.readUE();
    std::cout << "num_ref_frames="<<num_ref_frames<<std::endl;
    
    gaps_in_frame_num_value_allowed_flag = (source.readU(1) == 1);

    tmp = source.readUE();
    width = (tmp+1)*16;
    std::cout << "pic_width_in_mbs_minus1="<<tmp<<std::endl;
    std::cout << "width="<<width<<std::endl;
    
    uint32_t pic_height_in_map_units = source.readUE()+1;
    std::cout <<"pic_height_in_map_units="<<pic_height_in_map_units<<std::endl;
    
    frame_mbs_only_flag = (source.readU(1) == 1);
    std::cout << "frame_mbs_only_flag="<<frame_mbs_only_flag<<std::endl;
    
    mb_adaptive_frame_field_flag = false;
    if(!frame_mbs_only_flag) {
        mb_adaptive_frame_field_flag = (source.readU(1) == 1);
    }
    
    bool is_frame = true;
    uint32_t map_units;
    if(!frame_mbs_only_flag && mb_adaptive_frame_field_flag && is_frame) {
        map_units = 32;
        
    } else if(frame_mbs_only_flag || !is_frame) {
        map_units = 16;
    
    } else {
        map_units = 32;
    }
    
    height = pic_height_in_map_units * map_units;
    std::cout << "height = "<<height<<std::endl;
    
    direct_8x8_inference_flag = (source.readU(1) == 1);
    frame_cropping_flag       = (source.readU(1) == 1);
    
    std::cout << "frame cropping flag "<<frame_cropping_flag<<std::endl;
    
    frame_crop_left_offset   = source.readUE();
    frame_crop_right_offset  = source.readUE();
    frame_crop_top_offset    = source.readUE();
    frame_crop_bottom_offset = source.readUE(); 
    
    std::cout <<   "left="<<frame_crop_left_offset
              << " right="<<frame_crop_right_offset
              <<   " top="<<frame_crop_top_offset
              <<" bottom="<<frame_crop_bottom_offset<<std::endl;

    vui_parameters_present_flag       = (source.readU(1) == 1);
    std::cout << "have vui "<<vui_parameters_present_flag<<std::endl;
 
    
} // end of read method
