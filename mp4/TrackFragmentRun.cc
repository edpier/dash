#include "TrackFragmentRun.h"

#include "Box.h"
#include "MP4Exception.h"
  
/*******************************************************************************//**
*
**********************************************************************************/
TrackFragmentRun::TrackFragmentRun() 
                : Contents("trun") {
                    
    version = 0;
    flags = 0;
    
} // end of constructor
  
/******************************************************************************//**
*
**********************************************************************************/
TrackFragmentRun::~TrackFragmentRun() {
    
    clear();
    
} // end of destructor

/******************************************************************************//**
*
**********************************************************************************/
void TrackFragmentRun::clear() {
    
    for(Entries::iterator it = entries.begin(); it != entries.end(); ++it) {
        delete *it;
    }
    
    entries.clear();
    
} // end of clear

/******************************************************************************//**
*
**********************************************************************************/
void TrackFragmentRun::setDataOffset(int32_t data_offset) {
    
    this->data_offset = data_offset;
    flags |= 0x000001;
    
} // end of setDataOffset method
    
/******************************************************************************//**
*
**********************************************************************************/
void TrackFragmentRun::setFirstSampleFlags(uint32_t first_sample_flags) {
    
    this->first_sample_flags = first_sample_flags;
    flags |= 0x000004;
    
} // end of setFirstSampleFlags method

/******************************************************************************//**
*
**********************************************************************************/
void TrackFragmentRun::add() {
    
    TFREntry* entry = new TFREntry();
    entries.push_back(entry);
    
} // end of add method

/******************************************************************************//**
*
**********************************************************************************/
void TrackFragmentRun::setSampleDuration(uint32_t sample_duration) {
    
    if(entries.size() == 0) throw MP4Exception("No current entry");
    
    TFREntry* entry = entries[entries.size()-1];
    entry->sample_duration = sample_duration;
    
    flags |= 0x000100;
    
} //end of setSampleDuration method

/******************************************************************************//**
*
**********************************************************************************/
void TrackFragmentRun::setSampleSize(uint32_t sample_size) {
        
    if(entries.size() == 0) throw MP4Exception("No current entry");
    
    TFREntry* entry = entries[entries.size()-1];
    entry->sample_size = sample_size;
    
    flags |= 0x000200;
    
} // end of setSampleSize

/******************************************************************************//**
*
**********************************************************************************/
void TrackFragmentRun::setSampleFlags(uint32_t sample_flags) {
        
    if(entries.size() == 0) throw MP4Exception("No current entry");
    
    TFREntry* entry = entries[entries.size()-1];
    entry->sample_flags = sample_flags;
    
    flags |= 0x000400;
    
} // end of setSampleFlags

/******************************************************************************//**
*
**********************************************************************************/
void TrackFragmentRun::setSampleCompositionTimeOffset(
                                              uint32_t sample_composition_time_offset) {
        
    if(entries.size() == 0) throw MP4Exception("No current entry");
    
    TFREntry* entry = entries[entries.size()-1];
    entry->sample_composition_time_offset = sample_composition_time_offset;
    
    flags |= 0x000800;
    
} // end of setSampleCompositionTimeOffset method
    
/******************************************************************************//**
*
**********************************************************************************/
uint64_t TrackFragmentRun::getSize() const {
    
    uint64_t size = 8;
    
    if(flags&0x000001) size += 4;
    if(flags&0x000004) size += 4;
    if(flags&0x000100) size += 4*entries.size();
    if(flags&0x000200) size += 4*entries.size();
    if(flags&0x000400) size += 4*entries.size();
    if(flags&0x000800) size += 4*entries.size();
    
    return size;
    
} // end of getSize method

/******************************************************************************//**
*
**********************************************************************************/
void TrackFragmentRun::read(ByteSource& source) {
    
    version = source.readUint8();
    flags   = source.readBits(24);
    std::cout <<"version="<<version<<" flags="<<flags<<std::endl;
    
    uint32_t sample_count =source.readUint32();

    if(flags&0x000001) data_offset = source.readInt32();
    if(flags&0x000004) first_sample_flags = source.readUint32();
    
    if(flags&0x000001) std::cout << "data_offset="<<data_offset<<std::endl;
    if(flags&0x000004) std::cout << "first_sample_flags="<<first_sample_flags<<std::endl;
    
    clear();
    for(int i=0; i<(int)sample_count; ++i) {
        add();
        TFREntry* entry = entries[entries.size()-1];
        
        if(flags&0x000100) entry->sample_duration = source.readUint32();
        if(flags&0x000200) entry->sample_size     = source.readUint32();
        if(flags&0x000400) entry->sample_flags    = source.readUint32();
        if(flags&0x000800) entry->sample_composition_time_offset = source.readUint32();
        
        std::cout<< i;
        if(flags&0x000100) std::cout << " sample_duration="<<entry->sample_duration;
        if(flags&0x000200) std::cout << " sample_size="<<entry->sample_size;
        if(flags&0x000400) std::cout << " sample_flags="<<std::hex<<entry->sample_flags<<std::dec;
        if(flags&0x000800) std::cout << " sample_composition_time_offset="
                                          <<entry->sample_composition_time_offset;
        std::cout<<std::endl;
        
    }
    
} // end if read method

/******************************************************************************//**
*
**********************************************************************************/
void TrackFragmentRun::write(ByteSink& sink) const {
    
    sink.writeUint8(version);
    sink.writeBits(flags, 24);
    
    sink.writeUint32(entries.size());

    if(flags&0x000001) sink.writeInt32(data_offset);
    if(flags&0x000004) sink.writeUint32(first_sample_flags);
    
    for(Entries::const_iterator it = entries.begin(); it != entries.end(); ++it) {
        const TFREntry* entry = *it;

        if(flags&0x000100) sink.writeUint32(entry->sample_duration);
        if(flags&0x000200) sink.writeUint32(entry->sample_size);
        if(flags&0x000400) sink.writeUint32(entry->sample_flags);
        if(flags&0x000800) sink.writeUint32(entry->sample_composition_time_offset);
        
    }
    
} // end of write method
