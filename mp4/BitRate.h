#ifndef BIT_RATE_H
#define BIT_RATE_H

#include "Contents.h"

/**************************************************************************//**
*
******************************************************************************/
class BitRate : public Contents {
    
private:
    uint32_t decoding_buffer_size;
    uint32_t max_bit_rate;
    uint32_t avg_bit_rate;


    
public:
    BitRate();
    virtual ~BitRate() {}
    
    uint64_t getSize() const;
    void read(ByteSource& source);
    void write(ByteSink& sink) const;
    
}; // end of AVCSampleEntryclass
#endif
