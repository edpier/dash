#include "TrackFragmentHeader.h"

#include "Box.h"
  
/******************************************************************************//**
*
**********************************************************************************/
TrackFragmentHeader::TrackFragmentHeader() 
                : Contents("tfhd") {
                    
    version = 0;
    flags = 0;
    
    track_ID = 1;
    
} // end of constructor

/******************************************************************************//**
*
**********************************************************************************/
void TrackFragmentHeader::setTrackID(uint32_t track_id) {
    
    this->track_ID = track_id;
    
} // end of setTrackID method

/******************************************************************************//**
*
**********************************************************************************/
void TrackFragmentHeader::setBaseDataOffset(uint64_t base_data_offset) {
    
    this->base_data_offset = base_data_offset;
    flags |= 0x000001;
    
} // end of setBaseDataOffset method
    
/******************************************************************************//**
*
**********************************************************************************/
void TrackFragmentHeader::setSampleDescriptionIndex(uint32_t sample_description_index) {
    
    this->sample_description_index = sample_description_index;
    flags |= 0x000002;

} // end of setSampleDescriptionIndex
    
/**************************************************************************************//**
*
******************************************************************************************/
void TrackFragmentHeader::setDefaultSampleDuration(uint32_t default_sample_duration) {
    
    this->default_sample_duration = default_sample_duration;
    flags |= 0x000008;
    
} // end of setDefaultSampleDuration method
    
/******************************************************************************//**
*
**********************************************************************************/
void TrackFragmentHeader::setDefaultSampleSize(uint32_t default_sample_size) {
    
    this->default_sample_size = default_sample_size;
    flags |= 0x000010;
    
} // end of setDefaultSampleSize method
    
/**************************************************************************************//**
*
******************************************************************************************/
void TrackFragmentHeader::setDefaultSampleFlags(uint32_t default_sample_flags) {
    
    this->default_sample_flags = default_sample_flags;
    flags |= 0x000020;
    
} // end of setDefaultSampleFlags method

/******************************************************************************//**
*
**********************************************************************************/
uint64_t TrackFragmentHeader::getSize() const {
    
    uint64_t size = 8;
    if(flags&0x000001) size += 8;
    if(flags&0x000002) size += 4;
    if(flags&0x000008) size += 4;
    if(flags&0x000010) size += 4;
    if(flags&0x000020) size += 4;
    
    return size;
    
} // end of getSize method

/******************************************************************************//**
*
**********************************************************************************/
void TrackFragmentHeader::read(ByteSource& source) {
    
    version = source.readUint8();
    flags   = source.readBits(24);
    
    std::cout <<"version="<<version<<" flags="<<std::hex<<flags<<std::dec<<std::endl;
    
    track_ID = source.readUint32();
    std::cout <<"trac_ID="<<track_ID<<std::endl;
    
    if(flags&0x000001) std::cout << "base_data_offset="<<base_data_offset<<std::endl;
    if(flags&0x000002) std::cout << "sample_description_index="<<sample_description_index<<std::endl;
    if(flags&0x000008) std::cout << "default_sample_duration="<<default_sample_duration<<std::endl;
    if(flags&0x000010) std::cout << "default_sample_size="<<default_sample_size<<std::endl;
    if(flags&0x000020) std::cout << "default_sample_flags="<<default_sample_flags<<std::endl;

    if(flags&0x000001) base_data_offset = source.readUint64();
    if(flags&0x000002) sample_description_index = source.readUint32();
    if(flags&0x000008) default_sample_duration = source.readUint32();
    if(flags&0x000010) default_sample_size = source.readUint32();
    if(flags&0x000020) default_sample_flags = source.readUint32();
    
} // end of read method

/******************************************************************************//**
*
**********************************************************************************/
void TrackFragmentHeader::write(ByteSink& sink) const {
    
    sink.writeUint8(version);
    sink.writeBits(flags, 24);
    

    sink.writeUint32(track_ID);
    
    if(flags&0x000001) sink.writeUint64(base_data_offset);
    if(flags&0x000002) sink.writeUint32(sample_description_index);
    if(flags&0x000008) sink.writeUint32(default_sample_duration);
    if(flags&0x000010) sink.writeUint32(default_sample_size);
    if(flags&0x000020) sink.writeUint32(default_sample_flags);
    
} // end of read method
