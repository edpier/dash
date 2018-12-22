#ifndef URL_H
#define URL_H

#include <string>

#include <curl/curl.h>

/*********************************************************************************//**
*
*************************************************************************************/
class URL {

private:
    CURL* conn = curl_easy_init();
    
    char error_msg[CURL_ERROR_SIZE];
    
    std::string body;
    
public:
    URL();
    virtual ~URL();
    
    void setURL(const std::string& url);
    void go();
    
    const std::string& getBody() const;
    
private:
    static bool globalInit();
    
    void setOpt(CURLoption option, const void* parameter);
    
    void headerData(char *ptr, size_t size, size_t nmemb);
    void   bodyData(char *ptr, size_t size, size_t nmemb);
    
    friend int header_callback(char *ptr, size_t size, size_t nmemb, void *user_data);
    friend int   body_callback(char *ptr, size_t size, size_t nmemb, void *user_data);
    
}; // end of URL class


#endif
