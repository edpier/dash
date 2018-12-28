#include <iostream>

#include "URL.h"

int main(int argc, char** argv) {
    
    std::string api_key="7lCDEYXw3mM&key=AIzaSyAopRhAc3mo-4EJtDqSl1cTj0nvd1aL-74";
    
    std::string client_id = "751350549186-fsqjgh9r5rrhd7list865on3jvdosnfe.apps.googleusercontent.com";
    
    std::string client_secret = "dHEST0WHWgZnaLMpLnC0Ix-a";
    
    
    
    URL oauth_url;
    oauth_url.setScheme("https");
    oauth_url.setHost("accounts.google.com");
    oauth_url.setPath("/o/oauth2/auth");
    oauth_url.addQueryElement("client_id", client_id);
    //oauth_url.addQueryElement("redirect_uri", "http://localhost/oauth2callback");
    oauth_url.addQueryElement("redirect_uri", "urn:ietf:wg:oauth:2.0:oob");
    oauth_url.addQueryElement("scope", "https://www.googleapis.com/auth/youtube");
    oauth_url.addQueryElement("response_type", "code");
    oauth_url.addQueryElement("access_type", "offline");
    
    std::string string;
    oauth_url.toString(string);
    std::cout <<string<<std::endl;
    
    oauth_url.get();
    
    std::cout << oauth_url.getBody()<<std::endl;
    exit(1);
    
    
    std::string code = "4/wQDb20t3xHX8UPYgYbuFBdqWadLMyvXQ2dz5sttQw695N4dJCRHw7UY";
    
    URL url;
    url.setScheme("https");
    url.setHost("accounts.google.com");
    url.setPath("/o/oauth2/token");
    url.addQueryElement("code", code);
    url.addQueryElement("client_id", client_id);
    url.addQueryElement("client_secret", "dHEST0WHWgZnaLMpLnC0Ix-a");
    url.addQueryElement("redirect_uri", "urn:ietf:wg:oauth:2.0:oob");
    url.addQueryElement("grant_type", "authorization_code");
    
    url.post();
    std::cout << url.getBody()<<std::endl;
    
//     URL url;
//     url.setScheme("https");
//     url.setHost("www.googleapis.com");
//     url.setPath("/youtube/v3/videos");
//     url.addQueryElement("id", api_key);
//     url.addQueryElement("part", "snippet,contentDetails,statistics,status");
    

    
    //url.setURL("http://www.google.com");
//     url.setURL("https://www.googleapis.com/youtube/v3/videos?id=7lCDEYXw3mM&key=AIzaSyAopRhAc3mo-4EJtDqSl1cTj0nvd1aL-74&part=snippet,contentDetails,statistics,status");
    
    //url.get();
    
    //std::cout << url.getBody()<<std::endl;

} // end of main
