#include "EventMessage.h"

#include "Box.h"
  
/******************************************************************************//**
*
**********************************************************************************/
EventMessage::EventMessage() 
                : Contents("emsg") {
    
    message_data = NULL;
    
} // end of constructor

/******************************************************************************//**
*
**********************************************************************************/
uint64_t EventMessage::getSize() const {
    
    return scheme_id_uri.length()+1+value.length()+1+16+ndata;
    
} // end of getSize method

/******************************************************************************//**
*
**********************************************************************************/
void EventMessage::read(ByteSource& source) {
    
    version = source.readUint8();
    flags   = source.readBits(24);
    
    std::cout <<"version="<<version<<" flags="<<flags<<std::endl;
    
    source.readString(scheme_id_uri);
    source.readString(value);
    timescale = source.readUint32();
    presentation_time_delta = source.readUint32();
    event_duration = source.readUint32();
    id = source.readUint32();
    
    ndata = source.getRemaining();
    delete [] message_data;
    message_data = new uint8_t[ndata];
    if(ndata>0) {
        source.read(message_data, ndata);
    }
    
    std::cout << "scheme_id_uri="<<scheme_id_uri<<std::endl;
    std::cout << "value="<<value<<std::endl;
    std::cout << "timescale="<<timescale<<std::endl;
    std::cout << "presentation_time_delta="<<presentation_time_delta<<std::endl;
    std::cout << "event_duration="<<event_duration<<std::endl;
    std::cout << "ndata="<<ndata<<std::endl;
    
    for(int i=0; i<(int)ndata; ++i) {
        std::cout << "    "<<i<<" "<<(int)message_data[i]<<" "<<message_data[i]<<std::endl;
    }
    
} // end of read method

/******************************************************************************//**
*
**********************************************************************************/
void EventMessage::write(ByteSink& sink) const {
    
    sink.writeUint8(version);
    sink.writeBits(flags, 24);
    
    sink.writeString(scheme_id_uri);
    sink.writeString(value);
    sink.writeUint32(timescale);
    sink.writeUint32(presentation_time_delta);
    sink.writeUint32(event_duration);
    sink.writeUint32(id);
    
    if(ndata>0) {
        sink.write(message_data, ndata);
    }
    
} // end of write method
