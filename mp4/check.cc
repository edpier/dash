#include <fstream>

#include "Box.h"
#include "StreamByteSource.h"

int main(int argc, char** argv) {
    
    StreamByteSource source(new std::ifstream("out2.mp4"));
    
    Box box;
    while(true) {
        box.read(source);
    }
    
} // end of main
