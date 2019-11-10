#include "TimeToSample.h"

#include "Box.h"
  
/******************************************************************************//**
*
**********************************************************************************/
TimeToSample::TimeToSample() 
                : Contents("stts") {
    
} // end of constructor

/******************************************************************************//**
*
**********************************************************************************/
void TimeToSample::clear() {
    
    for(Entries::iterator it = entries.begin(); it != entries.end(); ++it) {
        delete *it;

    } // end of loop over entries
    
    entries.clear();
    
} // end of clear method

/******************************************************************************//**
*
**********************************************************************************/
void TimeToSample::add(uint32_t sample_count, uint32_t sample_delta) {
    
    TimeToSampleEntry* entry = new TimeToSampleEntry();
    entry->sample_count = sample_count;
    entry->sample_delta = sample_delta;
    
    entries.push_back(entry);
    
} // end of add method

/******************************************************************************//**
*
**********************************************************************************/
uint64_t TimeToSample::getSize() const {
    
    return 8 + entries.size()*8;

} // end of getSize method


/******************************************************************************//**
*
**********************************************************************************/
void TimeToSample::read(ByteSource& source) {
    
    version = source.readUint8();
    flags   = source.readBits(24);

    uint32_t entry_count = source.readUint32();
    std::cout << "entry_count="<<entry_count<<std::endl;
    
    for(int i=0; i<(int)entry_count; ++i) {
        uint32_t sample_count = source.readUint32();
        uint32_t sample_delta = source.readUint32();
        add(sample_count, sample_delta);
        
        std::cout << i<<" "<<"sample_count="<<sample_count
                          <<" sample_delta="<<sample_delta<<std::endl;

    } // end of loop over entries
    
} // end of read method

/******************************************************************************//**
*
**********************************************************************************/
void TimeToSample::write(ByteSink& sink) const {
    
    sink.writeUint8(version);
    sink.writeBits(flags, 24);
    
    sink.writeUint32(entries.size());
    
    for(Entries::const_iterator it = entries.begin(); it != entries.end(); ++it) {
        TimeToSampleEntry& entry = **it;

        sink.writeUint32(entry.sample_count);
        sink.writeUint32(entry.sample_delta);

    } // end of loop over entries
    
} // end of write method
