#include "TrackExtends.h"

#include "Box.h"
  
/******************************************************************************//**
*
**********************************************************************************/
TrackExtends::TrackExtends() 
                : Contents("trex") {
                    
    version = 0;
    flags   = 0;
    
    track_ID                         = 1;
    default_sample_description_index = 1;
    default_sample_duration          = 0;
    default_sample_size              = 0;
    default_sample_flags             = 0;                  
                    
    
} // end of constructor

/*********************************************************************//**
*
*************************************************************************/
uint64_t TrackExtends::getSize() const {
    
    return 24;
    
} // end of getSize method

/*********************************************************************//**
*
*************************************************************************/
void TrackExtends::read(ByteSource& source) {
    
    version = source.readUint8();
    flags   = source.readBits(24);
    
    std::cout <<"version="<<version<<" flags="<<flags<<std::endl;
    
    track_ID                         = source.readUint32();
    default_sample_description_index = source.readUint32();
    default_sample_duration          = source.readUint32();
    default_sample_size              = source.readUint32();
    default_sample_flags             = source.readUint32();
    
    std::cout << "track_ID="<<track_ID<<std::endl;
    std::cout << "default_sample_description_index="
              <<default_sample_description_index<<std::endl;
              
     std::cout << "default_sample_duration="<<default_sample_duration<<std::endl;   
     std::cout << "default_sample_size="<<default_sample_size<<std::endl;   
     std::cout << "default_sample_flags="<<default_sample_flags<<std::endl;  
     
} // end if read method

/*********************************************************************//**
*
*************************************************************************/
void TrackExtends::write(ByteSink& sink) const {
    
    sink.writeUint8(version);
    sink.writeBits(flags, 24);
    
    sink.writeUint32(track_ID);
    sink.writeUint32(default_sample_description_index);
    sink.writeUint32(default_sample_duration);
    sink.writeUint32(default_sample_size);
    sink.writeUint32(default_sample_flags);
    
} // end of write method
