#ifndef URL_H
#define URL_H

#include <string>
#include <vector>

#include <curl/curl.h>
#include <json/json.h>

/*********************************************************************************//**
*
*************************************************************************************/
class URL {

private:
    CURL* conn = curl_easy_init();
    
    char error_msg[CURL_ERROR_SIZE];
    
    std::string body;
    mutable Json::Value json_body;
    
    std::string scheme;
    std::string host;
    std::string port;
    std::string path;
    
    typedef std::pair<std::string, std::string> QueryElement;
    typedef std::vector<QueryElement> Query;
    Query query;
    
    struct curl_slist* headers;
    
public:
    URL();
    virtual ~URL();
    
    void setScheme(const std::string& scheme);
    void setHost(const std::string& host);
    void setPath(const std::string path);
    
    void addQueryElement(const std::string& key, const std::string value);
    void setQueryElement(const std::string& key, const std::string value);
    
    void clearQuery();
    
    void addHeader(const std::string& key, const std::string& value);
    
    void toString(std::string& url, bool get=true) const;
    void makeQueryString(std::string& query) const;
    
    void setURL(const std::string& url);
    
    void get();
    void post();
    void post(const std::string& data);
    void postJSON(const Json::Value& json);
    
    void del();
    
    const std::string& getBody() const;
    const Json::Value& getJSONBody() const;
    
    static void unescape(const std::string& orig, std::string& escaped);
    static void decode(const std::string& string, std::map<std::string, std::string>& map);
    
private:
    static bool globalInit();
    
    void setOpt(CURLoption option, const void* parameter);
    void perform();
    
    void headerData(char *ptr, size_t size, size_t nmemb);
    void   bodyData(char *ptr, size_t size, size_t nmemb);
    
    friend int header_callback(char *ptr, size_t size, size_t nmemb, void *user_data);
    friend int   body_callback(char *ptr, size_t size, size_t nmemb, void *user_data);
    
    static void escape(const std::string& orig, std::string& escaped);
    static bool isUnreserved(char c);
    
    
    
}; // end of URL class


#endif
