#ifndef EVENT_MESSAGE_HEADER_H
#define EVENT_MESSAGE_HEADER_H

#include "Contents.h"
  
/**************************************************************************************//**
*
******************************************************************************************/
class EventMessage : public Contents {
    
private:
    int version;
    uint32_t flags;
    
    std::string scheme_id_uri;
    std::string value;
    uint32_t timescale;
    uint32_t presentation_time_delta;
    uint32_t event_duration;
    uint32_t id;
    uint8_t* message_data;
    uint64_t ndata;

    
    
public:
    EventMessage();
    virtual ~EventMessage() {}
    
    uint64_t getSize() const;
    void read(ByteSource& source);
    void write(ByteSink& sink) const;
    
}; // end of EventMessage class
#endif
