#include "SampleToChunk.h"

#include "Box.h"
  
/******************************************************************************//**
*
**********************************************************************************/
SampleToChunk::SampleToChunk() 
                : Contents("stsc") {
    
} // end of constructor

/******************************************************************************//**
*
**********************************************************************************/
void SampleToChunk::clear() {
    
    for(Entries::iterator it = entries.begin(); it != entries.end(); ++it) {
        delete *it;

    } // end of loop over entries
    
    entries.clear();
    
} // end of clear method

/******************************************************************************//**
*
**********************************************************************************/
void SampleToChunk::add(uint32_t first_chunk, 
            uint32_t samples_per_chunk, 
            uint32_t sample_description_index) {
    
    SampleToChunkEntry* entry = new SampleToChunkEntry();
    entry->first_chunk              = first_chunk;
    entry->samples_per_chunk        = samples_per_chunk;
    entry->sample_description_index = sample_description_index;
     
    entries.push_back(entry);
    
} // end of add method

/******************************************************************************//**
*
**********************************************************************************/
uint64_t SampleToChunk::getSize() const {
    
    return 8 + entries.size()*12;

} // end of getSize method

/******************************************************************************//**
*
**********************************************************************************/
void SampleToChunk::read(ByteSource& source) {
    
    version = source.readUint8();
    flags   = source.readBits(24);
    
    std::cout <<"version="<<version<<" flags="<<flags<<std::endl;
    
    uint32_t entry_count = source.readUint32();
    std::cout << "entry_cout="<<entry_count<<std::endl;
    for(int i=0; i<(int)entry_count; ++i) {
        
        uint32_t first_chunk = source.readUint32();
        uint32_t samples_per_chunk = source.readUint32();
        uint32_t sample_description_index = source.readUint32();
        
        add(first_chunk, samples_per_chunk, sample_description_index);
        
        std::cout << i<<" "<<first_chunk<<" "<<samples_per_chunk<<" "<<sample_description_index<<std::endl;
        
    } // end of loop over entries
    
} // end of read method

/******************************************************************************//**
*
**********************************************************************************/
void SampleToChunk::write(ByteSink& sink) const {
        
    sink.writeUint8(version);
    sink.writeBits(flags, 24);
    
    sink.writeUint32(entries.size());

    for(Entries::const_iterator it = entries.begin(); it != entries.end(); ++it) {
        SampleToChunkEntry& entry = **it;
        
        sink.writeUint32(entry.first_chunk);
        sink.writeUint32(entry.samples_per_chunk);
        sink.writeUint32(entry.sample_description_index);
        
    } // end of loop over entries
    
} // end of wrote method
