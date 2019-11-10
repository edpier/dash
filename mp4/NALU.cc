#include "NALU.h"

#include <iostream>

#include "BitSource.h"
#include "MP4Exception.h"
#include "NALUUnescaper.h"
#include "SPS.h"

/**************************************************************************//**
*
******************************************************************************/
NALU::NALU() {
    
    contents = NULL;
    
} // end of constructor

/**************************************************************************//**
*
******************************************************************************/
NALU::~NALU() {
    
    delete contents;
    
} // end of destructor
      
/**************************************************************************//**
*
******************************************************************************/ 
NALUContents* NALU::getContents() { return contents; }

      
/**************************************************************************//**
*
******************************************************************************/  
void NALU::read(ByteSource& source) {
    
    NALUUnescaper unescaper(source);
    BitSource bits(unescaper);
    
    bits.readU(1); // forbidden bit
    nal_ref_idc = bits.readU(2);
    nal_unit_typ = bits.readU(5);
    
    std::cout << "nal_ref_idc="<<nal_ref_idc<<" "
              << "nal_unit_typ="<<nal_unit_typ<<std::endl;
    
    delete contents;
    
    if(nal_unit_typ == 7) contents = new SPS();
    else {
        return;
        //throw MP4Exception("unimplemented NALU type");
    }
    
    contents->read(bits);
    
} //end or read method
