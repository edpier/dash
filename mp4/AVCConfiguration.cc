#include "AVCConfiguration.h"

#include <cstring>

#include "Box.h"

/**************************************************************************//**
*
******************************************************************************/
AVCConfiguration::AVCConfiguration() 
              : Contents("avcC") {
                  
    configurationVersion = 1;
    AVCProfileIndication = 77;
    profileCompatibility = 64;
    AVCLevelIndication   = 31;
    
    length_size = 4;
    
    bit_depth_chroma = 8;
    bit_depth_luma   = 8;
    
} // end of constructor
  
/**************************************************************************//**
*
******************************************************************************/
AVCConfiguration::~AVCConfiguration() {
    
    for(ParameterSets::iterator it = spses.begin(); it != spses.end(); ++it) {
        delete *it;
    }
       
    for(ParameterSets::iterator it = ppses.begin(); it != ppses.end(); ++it) {
        delete *it;
    }
    
} // end of destructor
  
/**************************************************************************//**
*
******************************************************************************/
uint8_t AVCConfiguration::getLengthSize() const { return length_size; }
  
/**************************************************************************//**
*
******************************************************************************/
void AVCConfiguration::addSPS(uint8_t* data, int size) {
    
    ParameterSet* set = new ParameterSet();
    set->setSize(size);
    memcpy(set->getData(), data, size);
    
    spses.push_back(set);
    
    AVCProfileIndication = data[1];
    profileCompatibility = data[2];
    AVCLevelIndication   = data[3];
    
} // end of addSPS method
    
/**************************************************************************//**
*
******************************************************************************/
void AVCConfiguration::addPPS(uint8_t* data, int size) {
    
    ParameterSet* set = new ParameterSet();
    set->setSize(size);
    memcpy(set->getData(), data, size);
    
    ppses.push_back(set);
    
} // end of addPPS method
/**************************************************************************//**
*
******************************************************************************/
uint64_t AVCConfiguration::getSize() const {
    
    uint64_t size = 7;
    
    for(ParameterSets::const_iterator it = spses.begin(); it != spses.end(); ++it) {
        ParameterSet& p = **it;
        size += p.getSize() + 2;
    }
    
    for(ParameterSets::const_iterator it = ppses.begin(); it != ppses.end(); ++it) {
        ParameterSet& p = **it;
        size += p.getSize() + 2;
    }   
    
    if(AVCProfileIndication == 100 ||
       AVCProfileIndication == 110 ||
       AVCProfileIndication == 122 ||
       AVCProfileIndication == 144   ) {
        size += 4;
    }
    
    return size;
    
} // end of getSize method
  
/**************************************************************************//**
*
******************************************************************************/
void AVCConfiguration::read(ByteSource& source) {
    
    configurationVersion = source.readUint8();
    AVCProfileIndication = source.readUint8();
    profileCompatibility = source.readUint8();
    AVCLevelIndication   = source.readUint8();
    
    std::cout << "config="<<(int)configurationVersion<<std::endl;
    std::cout << "profile="<<(int)AVCProfileIndication<<std::endl;
    std::cout << "compat="<<(int)profileCompatibility<<std::endl;
    std::cout << "level="<<(int)AVCLevelIndication<<std::endl;
    
    length_size = (source.readUint8() & 3)+1;
    std::cout << "length_size="<<(int)length_size<<std::endl;
    
    int n = source.readUint8() & ((1<<5)-1);
    std::cout << "SPS count="<<n<<std::endl;
    for(int i=0; i<n; ++i) {
        ParameterSet* s = new ParameterSet();
        s->read(source);
        spses.push_back(s);
    }

    n = source.readUint8() & ((1<<5)-1);
    std::cout << "PPS count="<<n<<std::endl;
    for(int i=0; i<n; ++i) {
        ParameterSet* s = new ParameterSet();
        s->read(source);
        ppses.push_back(s);
    }    
    
    std::cout << "AVCProfileIndication="<<(int)AVCProfileIndication<<std::endl;
    if(AVCProfileIndication == 100 ||
       AVCProfileIndication == 110 ||
       AVCProfileIndication == 122 ||
       AVCProfileIndication == 144   ) {
        
        uint8_t tmp = source.readUint8();
        chroma_format = tmp & 3;
        
        tmp = source.readUint8();
        bit_depth_luma = (tmp&7) + 8;
        
        tmp = source.readUint8();
        bit_depth_chroma = (tmp&7) + 8;
        
        std::cout << "chroma_format="<<(int)chroma_format<<std::endl;
        std::cout << "bit_depth_luma="<<(int)bit_depth_luma<<std::endl;
        std::cout << "bit_depth_chroma="<<(int)bit_depth_chroma<<std::endl;
        
        uint8_t n = source.readUint8();
        std::cout << "n="<<(int)n<<std::endl;
        if(n>0) {
            std::cerr << "param set ext not supported"<<std::endl;
            abort();
        }
    }
        
} // end of read method
  
/**************************************************************************//**
*
******************************************************************************/
void AVCConfiguration::write(ByteSink& sink) const {
    
    sink.writeUint8(configurationVersion);
    sink.writeUint8(AVCProfileIndication); // defined in part 10
    sink.writeUint8(profileCompatibility);
    sink.writeUint8(AVCLevelIndication);

    uint8_t field = 253 | (length_size-1);
    sink.writeUint8(field);

    
    uint8_t mask = ((1<<5)-1);
    
    int n = spses.size() & mask;
    field = (0xff-mask) | n;
    sink.writeUint8(field);

    for(int i=0; i<n; ++i) {
        ParameterSet* s = spses[i];
        s->write(sink);
    }
    
    n = ppses.size() & mask;
    field = (0xff-mask) | n;
    sink.writeUint8(field);

    for(int i=0; i<n; ++i) {
        ParameterSet* s = ppses[i];
        s->write(sink);
    }  
    
    if(AVCProfileIndication == 100 ||
       AVCProfileIndication == 110 ||
       AVCProfileIndication == 122 ||
       AVCProfileIndication == 144   ) {
        
        uint8_t tmp = (0xff<<2) | (chroma_format & 3);
        sink.writeUint8(tmp);
        
        tmp = (0xff<<3) | ((bit_depth_luma-8) & 7);
        sink.writeUint8(tmp);
        
        tmp = (0xff<<3) | ((bit_depth_chroma-8) & 7);
        sink.writeUint8(tmp); 
        
        sink.writeUint8(0); // numOfSequenceParameterSetExt;
//         for (i=0; i< numOfSequenceParameterSetExt; i++) {
//             unsigned int(16) sequenceParameterSetExtLength;
//             bit(8*sequenceParameterSetExtLength) sequenceParameterSetExtNALUnit;
//         }
        
    } 
    
} // end of write method
