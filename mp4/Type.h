#ifndef TYPE_H
#define TYPE_H

#include "Readable.h"

#include <iostream>
#include <cstdint>
#include <string>

#include "ByteSink.h"
#include "ByteSource.h"

class Type : public Readable {
    
private:
    std::string string;
    uint32_t code;
    
    
public:
    Type();
    Type(const std::string& type);
    Type(const Type& type);
    virtual ~Type() {}
    
    uint32_t getCode() const;
    const std::string& getString() const;
    static int getSize();
    
    void read(ByteSource& source);
    void write(ByteSink& sink) const;
    
    const Type& operator=(const Type& type);
    
    bool operator==(const std::string& string) const;
    //bool operator==(const char* string) const;
    
    bool operator!=(const std::string& string) const;
    
friend std::ostream& operator<<(std::ostream& out, const Type& type);
    
    
}; // end of type class

#endif
