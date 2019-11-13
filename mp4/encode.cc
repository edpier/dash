#include <cstring>
#include <fstream>

#include "DashEncoder.h"

/*********************************************************************//**
*
*************************************************************************/
int main(int argc, char** argv) {
    
    DashEncoder enc;
    
    std::ifstream in("../video.h264");
    
    int size = 1024;
    uint8_t* buffer = new uint8_t[size];
    
    int nzeros = 0;
    int offset = 0;
    while(in.good()) {
        
        int c = in.get();
        if(c == EOF) {
            // process last NALU
            enc.addNALU(buffer, offset);
            break;
        }
        
        /*****************
        * save this byte *
        *****************/
        if(offset>=size) {
            /************************
            * we need a bigger boat *
            ************************/
            std::cout<<"bigger size="<<size<<std::endl;
            uint8_t* tmp = new uint8_t[size*2];
            memcpy(tmp, buffer, size);
            delete [] buffer;
            buffer = tmp;
            size *= 2;
        }
        
        buffer[offset++] = c;
        
        //if(nzeros >0) std::cout <<"nzeros="<<nzeros<<std::endl;
        
        if(c == 0) ++nzeros;
        else if(nzeros == 3) {
            /**************************
            * looks like a start code *
            **************************/
            if(c != 1) {
                std::cerr << "bad start code"<<std::endl;
            } else {
                //std::cout << "NALU length = "<<offset<<" ";//<<std::endl;
//                 std::cout << (int)buffer[offset-4]<<" "
//                           << (int)buffer[offset-3]<<" "
//                           << (int)buffer[offset-2]<<" "
//                           << (int)buffer[offset-1]<<std::endl;
                          
                if(offset>4) enc.addNALU(buffer, offset-4);
            }
            
            nzeros = 0;
            offset = 0;
            
        } else {
            nzeros = 0;
        }
        
        
    } // end of loop over file
    
    
    
} // end of main
