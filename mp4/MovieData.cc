#include "MovieData.h"


/*********************************************************************//**
*
*************************************************************************/
MovieData::MovieData()
         : Contents("mdat") {
    
    
} // end of constructor
    
    
/*********************************************************************//**
*
*************************************************************************/
MovieData::~MovieData() {
    
    clear();
    
} // end of destructor

    
/*********************************************************************//**
*
*************************************************************************/
void MovieData::add(DataChunk* chunk) { chunks.push_back(chunk); }
    
/*********************************************************************//**
*
*************************************************************************/
void MovieData::clear() {

    for(Chunks::iterator it = chunks.begin(); it != chunks.end(); ++it) {
        delete *it;

    } // end of loop over chunks
    
    chunks.clear();
    
} // end of clear method
   
/*********************************************************************//**
*
*************************************************************************/ 
uint64_t MovieData::getSize() const {
    
    uint64_t size = 0;
    for(Chunks::const_iterator it = chunks.begin(); it != chunks.end(); ++it) {
        DataChunk& chunk = **it;
        
        size += chunk.getTotalSize();
        
    } // end of loop over chunks
    
    return size;
    
} // end of getSize method

/*********************************************************************//**
*
*************************************************************************/
void MovieData::read(ByteSource& source) {
    
    clear();
    
    std::cout << "reading NALUs"<<std::endl;
    
    /****************************************************************
    * NALUs are preceeded by a 32 bit field that gives their length *
    ****************************************************************/
    while(source.getRemaining()>0) {
        DataChunk* chunk = new DataChunk();
        chunk->read(source);
        chunks.push_back(chunk);
        
    } // end of loop over chunks

    
} // end of read method


/*********************************************************************//**
*
*************************************************************************/
void MovieData::write(ByteSink& sink) const {
    
    for(Chunks::const_iterator it = chunks.begin(); it != chunks.end(); ++it) {
        DataChunk& chunk = **it;
        
        chunk.write(sink);
        
    } // end of loop over chunks
} // end of read method
