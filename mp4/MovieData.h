#ifndef MOVIE_DATA_H
#define MOVIE_DATA_H

#include "Contents.h"

#include <vector>

#include "DataChunk.h"

/*****************************************************************************//**
*
*********************************************************************************/
class MovieData : public Contents {
    
private:
    typedef std::vector<DataChunk*> Chunks;
    Chunks chunks;
    
public:
    MovieData();
    virtual ~MovieData();
    
    void add(DataChunk* chunk);
    void clear();
    
    
    uint64_t getSize() const;
    void read(ByteSource& source);
    void write(ByteSink& sink) const;
    
}; // end of MovieData class

#endif
