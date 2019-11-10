#include <iostream>
#include <map>
#include <sstream>

#include "URL.h"


/*********************************************************************************//**
*
*************************************************************************************/
int main(int argc, char** argv) {
    
    
    URL url;
    url.setScheme("https");
    url.setHost("www.youtube.com");
    url.setPath("/get_video_info");
    url.addQueryElement("video_id", "7NhQO28BSb0");
    
    url.get();
    
    std::string body = url.getBody();
    
    typedef std::map<std::string, std::string> Map;
    Map map;
    URL::decode(url.getBody(), map);
    
    Map adaptive_fmts;
    URL::decode(map["adaptive_fmts"], adaptive_fmts);
    
    Map fflags;
    URL::decode(map["fflags"], fflags);
    
    Map url_encoded_fmt_stream_map;
    URL::decode(map["url_encoded_fmt_stream_map"], url_encoded_fmt_stream_map);
    
    
    std::istringstream s(map["player_response"]);
    Json::Value player_response;
    s >> player_response;
    
    std::cout << player_response["streamingData"]["dashManifestUrl"].asString() << std::endl;
    

//     Map thing;
//     URL::decode(url_encoded_fmt_stream_map["url"], thing);
//     
//     Map& dump = map;
//     for(Map::iterator it = dump.begin(); it != dump.end(); ++it) {
//         
//         const std::string& key = it->first;
//         const std::string& value = it->second;
//         
//         std::cout << key<<std::endl;
//         std::cout <<value<<std::endl;
//         std::cout << "______________________________________________________"<<std::endl;
//         
//     } // end of loop over fields
    
    
} // end of main
