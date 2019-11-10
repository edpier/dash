#include <iostream>
#include <sstream>

#include <json/json.h>

#include "URL.h"

/*********************************************************************************//**
*
*************************************************************************************/
int main(int argc, char** argv) {
    
    std::string api_key="AIzaSyAopRhAc3mo-4EJtDqSl1cTj0nvd1aL-74";
    
    std::string client_id = "751350549186-fsqjgh9r5rrhd7list865on3jvdosnfe.apps.googleusercontent.com";
    
    std::string client_secret = "dHEST0WHWgZnaLMpLnC0Ix-a";
    
    
    
    std::string token = 
    "ya29.GluCBpDsDfDkEp2ELodOaayC_sgwljqw4Wt4CtwUG-goAG1PKTT1E73O6mRrNNL2ZHqjzPlczgEJ6lF0rFAsGvwR0_g9zJmDtZY9J-9m2JYOG1B0jJ7SvqWvZ2CW";
    

    URL url;
    url.setScheme("https");
    url.setHost("www.googleapis.com");
    url.setPath("/youtube/v3/videos");
    //url.addHeader("Authorization", "Bearer "+token);
    url.addQueryElement("id", "7lCDEYXw3mM");
    url.addQueryElement("key", api_key);
    //url.addQueryElement("part", "snippet,contentDetails,statistics,status");
    url.addQueryElement("part", "fileDetails");
    
    url.get();
    
    std::cout << url.getBody()<<std::endl;

} // end of main
