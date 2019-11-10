#ifndef DATA_ENTRY_URL_H
#define DATA_ENTRY_URL_H

#include "Contents.h"

#include <string>
  
/**************************************************************************************//**
*
******************************************************************************************/
class DataEntryURL : public Contents {
    
private:
    int version;
    uint32_t flags;
    
    std::string url;

    
public:
    DataEntryURL();
    virtual ~DataEntryURL() {}
    
    void set(const std::string& url);
    
    uint64_t getSize() const;
    void read(ByteSource& source);
    void write(ByteSink& sink) const;
    
}; // end of DataEntryURL class
#endif
