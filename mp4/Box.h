#ifndef BOX_H
#define BOX_H

#include "Readable.h"

#include <cstdint>

#include "ByteSink.h"
#include "ByteSource.h"
#include "Contents.h"
#include "Size.h"
#include "Type.h"

/*******************************************************************************//**
*
***********************************************************************************/
class Box : public Readable {
    
private:
    
    Contents* contents;

public:
    Box();
    Box(Contents* contents);
    virtual ~Box();
    
    void setContents(Contents* contents);
    Contents* getContents();
    const Contents* getContents() const;
    
    uint64_t getSize() const;
    void read(ByteSource& source);
    void write(ByteSink& sink) const;

}; // end of Box class

#endif
