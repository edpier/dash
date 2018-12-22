#include <iostream>

#include "URL.h"

int main(int argc, char** argv) {
    
    URL url;
    //url.setURL("http://www.google.com");
    url.setURL("https://www.googleapis.com/youtube/v3/videos?id=7lCDEYXw3mM&key=AIzaSyAopRhAc3mo-4EJtDqSl1cTj0nvd1aL-74&part=snippet,contentDetails,statistics,status");
    
    url.go();
    
    std::cout << url.getBody()<<std::endl;

} // end of main
