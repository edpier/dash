#include "ItemList.h"

#include "Box.h"
#include "MP4Exception.h"
  
/******************************************************************************//**
*
**********************************************************************************/
ItemList::ItemList() 
    : Contents("ilst") {
    
} // end of constructor

/******************************************************************************//**
*
**********************************************************************************/
uint64_t ItemList::getSize() const {
    
    int size = 4;
//     for(Boxes::const_iterator it = boxes.begin(); it != boxes.end(); ++it) {
//         Box& box = **it;
//         
//         size += box.getSize();
//         
//     } // end of loop over boxes
    
    return size;
    
} // end of getSize method

/******************************************************************************//**
*
**********************************************************************************/
void ItemList::read(ByteSource& source) {
    
    Type tmp;
    for(int i=0; source.getRemaining()>0; ++i) {
        TagRecord* tag = new TagRecord();

        /***************************************
        * redundant size field (npayload + 24) *
        ***************************************/
        source.readUint32();
        
        /****************
        * name and size *
        ****************/
        tag->tag_name.read(source);
        tag->npayload = source.readUint32() - 16;
        
        /***********
        * sez data *
        ***********/
        tmp.read(source);
        if(tmp != "data") {
            throw MP4Exception("Corruped ilist element");
        }
        
        /************
        * data type *
        ************/
        tag->data_typ = source.readUint32();
        
        /*********
        * unused *
        *********/
        source.readUint32();
        
        /*******************
        * read the payload *
        *******************/
        tag->payload = new uint8_t[tag->npayload];
        source.read(tag->payload, tag->npayload);
        
        // debug
        std::cout <<"    "<<i<<" "<<tag->tag_name<<" length="<<tag->npayload
                  <<" type="<<tag->data_typ
                  <<std::endl;
                  
        std::cout << "|";
        for(int j=0; j<(int)(tag->npayload); ++j) {
            std::cout << tag->payload[j];
        }
        std::cout<<"|"<< std::endl;
        
        
    } // end of loop over tags

    
} // end of read method
