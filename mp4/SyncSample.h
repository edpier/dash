#ifndef SYNC_SAMPLE_H
#define SYNC_SAMPLE_H

#include "Contents.h"

#include <vector>
  
/**************************************************************************************//**
*
******************************************************************************************/
class SyncSample : public Contents {
    
private:
    int version;
    uint32_t flags;

    typedef std::vector<uint32_t> Entries;
    Entries entries;
    
public:
    SyncSample();
    virtual ~SyncSample() {}
           
    void clear();
    void add(uint32_t entry_size);

    uint64_t getSize() const; 
    void read(ByteSource& source);
    void write(ByteSink& sink) const;
    
}; // end of SyncSample class
#endif
