#include "Container.h"

#include "SubByteSource.h"

/***************************************************************************//**
*
*******************************************************************************/
Container::Container(const Type type) 
         : Contents(type) {
    
} // end of constructor

/**************************************************************************//**
*
******************************************************************************/
Container::Container(const std::string& type) 
         : Contents(type) {}

/**************************************************************************//**
*
******************************************************************************/
Container::~Container() {
    
    clear();
    
} // end of destructor

    
/**************************************************************************//**
*
******************************************************************************/
void Container::clear() {
    
    for(Boxes::iterator it = boxes.begin(); it != boxes.end(); ++it) {
        
        delete *it;
    }
    
    boxes.clear();
    
} // end of clear method
    
/***************************************************************************//**
* @details This class takes ownership of the box 
*******************************************************************************/
void Container::add(Box* box) {
    
    boxes.push_back(box);
    
} // end of add method
    
/**************************************************************************//**
* @details This class takes ownership of the container 
******************************************************************************/
void Container::add(Contents* contents) {
    
    add(new Box(contents));
    
} // end of add container method
    
/**************************************************************************//**
*
******************************************************************************/
Contents* Container::get(const std::string& type, int index) {
    
    int count = 0;
    return get(type, index, count);
    
} // end of getContents method


/**************************************************************************//**
*
******************************************************************************/
int Container::getBoxCount() const { return boxes.size(); }
    
/**************************************************************************//**
*
******************************************************************************/
uint64_t Container::getSize() const {
    
    uint64_t size = 0;
    for(Boxes::const_iterator it = boxes.begin(); it != boxes.end(); ++it) {
        const Box& box = **it;
        size += box.getSize();
        
    } // end of loop over boxes
    
    return size;
    
} // end of getSize method
    
/***************************************************************************//**
*
*******************************************************************************/
void Container::read(ByteSource& source) {

    while(source.getRemaining()>0) {
        Box* box = new Box();
        box->read(source);
        boxes.push_back(box);
    }
    
    
    
} // end of read method
    
/***************************************************************************//**
*
*******************************************************************************/
void Container::write(ByteSink& sink) const {
    
    for(Boxes::const_iterator it = boxes.begin(); it != boxes.end(); ++it) {
        const Box& box = **it;
        box.write(sink);
    } // end of loop over boxes
    
} // end of write method
    
/***************************************************************************//**
*
*******************************************************************************/
Contents* Container::get(const std::string& type, int index, int& count) {
    
    for(Boxes::iterator it = boxes.begin(); it != boxes.end(); ++it) {
        Box& box = **it;
        
        /***************************************
        * are these the droids we're look for? *
        ***************************************/
        Contents* contents = box.getContents();
        if(contents->getType() == type) {
            ++count;
            if(count>index) return contents;
        }
        
        /********************************
        * recurse through subcontainers *
        ********************************/
        Container* container = dynamic_cast<Container*>(contents);
        if(container != NULL) {
            contents = container->get(type, index, count);
            if(contents != NULL) return contents;
        }
        
    } // end of loop over boxes.
    
    return NULL;
    
} // end of get method
