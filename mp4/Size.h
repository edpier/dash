#include <iostream>

#include "ByteSource.h"
#include "ByteSink.h"

/*********************************************************************//**
*
*************************************************************************/
class Size {
    
private:
    uint64_t size;
    
    static const uint64_t MAX32;
    
public:
    Size();
    Size(uint64_t size);
    Size(const Size& size);
    virtual ~Size() {}
    
    void addHeader();
    
    uint64_t getValue();
    int getSize();
    
    void read(ByteSource& source);
    void write(ByteSink& sink);
    
    const Size& operator=(uint64_t size);
    const Size& operator=(const Size& size);
    
    operator uint64_t() const;
    
    friend std::ostream& operator<<(std::ostream& out, const Size& size);
    
}; // end of Size class
