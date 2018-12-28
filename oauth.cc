#include <iostream>
#include <sstream>

#include <json/json.h>

#include "URL.h"

/**********************************************************************************
* This code goes through the OAuth authentication procedure. 
* Run it, do what it sez and it will give you the OAuth token and a reresh token,
* in case you need that too.
***********************************************************************************/
int main(int argc, char** argv) {
    
    /****************************************************************
    * this string identifies the app that is registered with Google *
    ****************************************************************/
    std::string client_id = 
                    "751350549186-fsqjgh9r5rrhd7list865on3jvdosnfe.apps.googleusercontent.com";
                    
    std::string client_secret = "dHEST0WHWgZnaLMpLnC0Ix-a";
    
    /************************************************************************
    * construct a URL to paste into a browser to do the user authentication *
    ************************************************************************/
    URL url;
    url.setScheme("https");
    url.setHost("accounts.google.com");
    url.setPath("/o/oauth2/auth");
    url.addQueryElement("client_id", client_id);
    url.addQueryElement("redirect_uri", "urn:ietf:wg:oauth:2.0:oob");
    url.addQueryElement("scope", "https://www.googleapis.com/auth/youtube");
    url.addQueryElement("response_type", "code");
    url.addQueryElement("access_type", "offline");
    
    std::cout << "Paste the following URL into a browser and do what it says:"<<std::endl;
    std::cout << std::endl;
    
    std::string string;
    url.toString(string);
    std::cout << string<<std::endl<<std::endl;
    
    /***************************************************
    * Read the code that the user got from the browser *
    ***************************************************/
    std::cout << "Enter the code from the browser:"<<std::endl;
    std::string code;
    std::cin >> code;
    
    
    url.setPath("/o/oauth2/token");
    url.addQueryElement("code", code);
    url.addQueryElement("client_id", client_id);
    url.addQueryElement("client_secret", client_secret);
    url.addQueryElement("redirect_uri", "urn:ietf:wg:oauth:2.0:oob");
    url.addQueryElement("grant_type", "authorization_code");
    
    url.post();
    std::cout << url.getBody()<<std::endl;
    
    /*******************************************
    * Parse the returned JSON to get the token *
    *******************************************/
    Json::Value root;
    std::istringstream s(url.getBody());
    s >> root;
    
    std::cout << "Access Token:  "<<root[ "access_token"].asString()<<std::endl<<std::endl;
    std::cout << "Refresh Token: "<<root["refresh_token"].asString()<<std::endl;
    
    
    
    
    
} // end of main
