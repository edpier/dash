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
    
    /*******************
    * make a broadcast *
    *******************/
    URL url;
    url.setScheme("https");
    url.setHost("www.googleapis.com/youtube/v3");
    url.setPath("/liveBroadcasts");
    url.addHeader("Authorization", "Bearer "+token);
    
    //url.addQueryElement("part", "id,snippet,contentDetails,status");
    
    Json::Value json;
    json["snippet"]["title"] = "test stream";
    json["snippet"]["scheduledStartTime"] = "2018-12-31T00:00:00.0Z";
    json["status" ]["privacyStatus"] = "unlisted";

    //url.postJSON(json);
    
    //std::cout << url.getJSONBody()<<std::endl;
    
    //std::string id = url.getJSONBody()["id"].asString();
    //std::cout << "id="<<id<<std::endl;
    
    url.addQueryElement("id", "VFjKQ1DNp8Y");
    url.del();
    std::cout << url.getBody()<<std::endl;
    
    /********************
    * now make a stream *
    ********************/
    url.setPath("/liveStreams");
    //url.setQueryElement("part", "id,snippet,cdn,contentDetails,status");
    
    Json::Value json2;
    json2["snippet"]["title"] = "test";
    json2["cdn"]["frameRate"] = "30fps";
    json2["cdn"]["resolution"] = "1080p";
    json2["cdn"]["ingestionType"] = "dash";
    
    //url.postJSON(json2);
    
    url.setQueryElement("id", "jmHxHTnMCFTY5n_jBDirXg1546135527348545");
    //url.del();
    
    std::cout << url.getBody()<<std::endl;
    
    



     
//     URL url;
//     url.setScheme("https");
//     url.setHost("www.googleapis.com");
//     url.setPath("/youtube/v3/videos");
//     //url.addHeader("Authorization", "Bearer "+token);
//     url.addQueryElement("id", "7lCDEYXw3mM");
//     url.addQueryElement("key", api_key);
//     //url.addQueryElement("part", "snippet,contentDetails,statistics,status");
//     url.addQueryElement("part", "snippet");
//     
//     url.get();
//     
//     std::cout << url.getBody()<<std::endl;

} // end of main
