#include "URL.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "URLException.h"

/*****************************************************************/ /**
* @brief Callback for header data
*********************************************************************/
int header_callback(char *ptr, size_t size, size_t nmemb, void *user_data){

    URL* url = (URL*)user_data;
    url->headerData(ptr, size, nmemb);
    
    return size*nmemb;

} // end of header_callback function

/*****************************************************************/ /**
* @brief Callback for body data
*********************************************************************/
int body_callback(char *ptr, size_t size, size_t nmemb, void *user_data){

    URL* url = (URL*)user_data;
    url->bodyData(ptr, size, nmemb);
    
    return size*nmemb;

} // end of body_callback function

/*********************************************************************************//**
*
*************************************************************************************/
URL::URL() {
    
    /*****************************
    * this will only happen once *
    *****************************/
    static bool initialized = globalInit();
    
    /************************
    * create the connection *
    ************************/
    conn = curl_easy_init();
    
    /***************************
    * set error message buffer *
    ***************************/
    error_msg[0] = '\0'; // just in case;
    setOpt(CURLOPT_ERRORBUFFER, error_msg);
    
    /*****************
    * custom headers *
    *****************/
    headers = NULL;
    
    
    /************
    * callbacks *
    ************/
    setOpt(CURLOPT_HEADERDATA, this);
    setOpt(CURLOPT_HEADERFUNCTION, (void*)header_callback);

    setOpt(CURLOPT_WRITEDATA, this);
    setOpt(CURLOPT_WRITEFUNCTION, (void*)body_callback);

    /***********
    * defaults *
    ***********/
    scheme = "http";
    
} // end of constructor

    
/*********************************************************************************//**
*
*************************************************************************************/
URL::~URL() {
    
} // end of destructor
    
/*********************************************************************************//**
*
*************************************************************************************/
void URL::setScheme(const std::string& scheme) { this->scheme = scheme; }
    
/*********************************************************************************//**
*
*************************************************************************************/
void URL::setHost(const std::string& host) { this->host = host; }
    
/*********************************************************************************//**
*
*************************************************************************************/
void URL::setPath(const std::string path) { this->path = path;}
    
/*********************************************************************************//**
*
*************************************************************************************/
void URL::addQueryElement(const std::string& key, const std::string value) {
    
    QueryElement elem;
    escape(key,   elem.first );
    escape(value, elem.second);
    
    query.push_back(elem);
    
} // end of addQueryElement
    
/*********************************************************************************//**
*
*************************************************************************************/
void URL::setQueryElement(const std::string& key, const std::string value) {
    
    for(Query::iterator it = query.begin(); it != query.end(); ++it) {
        
        QueryElement& elem = *it;
        
        if(elem.first == key) {
            /***********
            * found it *
            ***********/
            elem.second = value;
            return;
        }
        
        
    } // end of loop over existing query elements 
    
    /****************************************************
    * if we get here we do not already have the element *
    ****************************************************/
    QueryElement elem;
    escape(key,   elem.first );
    escape(value, elem.second);
    
    query.push_back(elem);
    
} // end of addQueryElement

/*********************************************************************************//**
*
*************************************************************************************/
void URL::clearQuery() { query.clear(); }

/*********************************************************************************//**
*
*************************************************************************************/
void URL::addHeader(const std::string& key, const std::string& value) {
    
    headers = curl_slist_append(headers, (key+": "+value).c_str());
    
} // end of addHeader method

/*********************************************************************************//**
*
*************************************************************************************/
void URL::toString(std::string& url, bool get) const {
    
    if(scheme == "") {
        throw URLException("No scheme");
    }
    
    url.clear();
    url += scheme+':';
    
    if( host != "") {
        url += "//";
        url += host;
        
        if(port != "") {
            url += ':';
            url += port;
        }
    } // end if there is a host
    
    url += path;
    
    if(get && query.size() >0) {

        std::string string;
        makeQueryString(string);
        
        url += '?';
        url += string;
        
    } // end if we are adding the query string
    
    
} // end of toString method
    
/*********************************************************************************//**
*
*************************************************************************************/
void URL::makeQueryString(std::string& string) const {
    
    string.clear();
    for(Query::const_iterator it = query.begin(); it != query.end(); ++it) {
            
        string += it->first;
        string += '=';
        string += it->second;
        
        if(it+1 != query.end()) string += '&';
        
    } // end of loop over query elements
    
} // end of makeQueryString method
    
/*********************************************************************************//**
*
*************************************************************************************/
void URL::get() {
    
    std::string url;
    toString(url);
    
    setOpt(CURLOPT_URL, const_cast<char*>(url.c_str()));
    
    
    perform();
    
} // end of get method
        
/*********************************************************************************//**
*
*************************************************************************************/
void URL::post() {
    
    /******************************************
    * assemble the URL without the query data *
    ******************************************/
    std::string url;
    toString(url, false);
    
    setOpt(CURLOPT_URL, const_cast<char*>(url.c_str()));
    
    /**************************************
    * make the query string separately
    * so we can send it in the body 
    **************************************/
    std::string string;
    makeQueryString(string);
    
    setOpt(CURLOPT_POSTFIELDS, string.c_str());
    
    
    perform();
    
} // end of post method
        
/*********************************************************************************//**
*
*************************************************************************************/
void URL::post(const std::string& data) {
    
    /******************************************
    * assemble the URL without the query data *
    ******************************************/
    std::string url;
    toString(url);
    
    setOpt(CURLOPT_URL, const_cast<char*>(url.c_str()));
    setOpt(CURLOPT_POSTFIELDS, data.c_str());
    
    perform();
    
} // end of post method

/*********************************************************************************//**
*
*************************************************************************************/
void URL::postJSON(const Json::Value& json) {
    
    addHeader("Content-Type", "application/json");
    
    std::ostringstream s;
    s << json;
    
    post(s.str());
    
} // end of post method

    
/*********************************************************************************//**
* @brief Make an HTTP DELETE call
*************************************************************************************/
void URL::del() {
    
    std::string url;
    toString(url);
    
    setOpt(CURLOPT_URL, const_cast<char*>(url.c_str()));
    setOpt(CURLOPT_CUSTOMREQUEST, "DELETE");
    
    perform();
    
} // end of del method


/*********************************************************************************//**
*
*************************************************************************************/
const std::string& URL::getBody() const {
    
    return body; 
    
} // end of getBody method

/*********************************************************************************//**
*
*************************************************************************************/
const Json::Value& URL::getJSONBody() const {
    
    std::istringstream s(body);
    s >> json_body;
    
    return json_body;
    
} // end of getJSONBody method
    
/*********************************************************************//**
*
*************************************************************************/
bool URL::globalInit() {
    
    curl_global_init(CURL_GLOBAL_DEFAULT);
    

    
} // end of globalInit static method
    
/*********************************************************************//**
*
*************************************************************************/
void URL::setOpt(CURLoption option, const void* parameter) {
    
    CURLcode status = curl_easy_setopt(conn, option, parameter);
    if(status != CURLE_OK) {
        std::string msg = "Error: ";
        msg += error_msg;
        throw URLException(msg);
    }
        
    
} // end of setOpt method
        
/*********************************************************************//**
*
*************************************************************************/
void URL::perform() {
    
    /**********************************
    * clear out any old response body *
    **********************************/
    body.clear();
    
    /*************************************
    * set custom headers, if we have any *
    *************************************/
    if(headers != NULL) {
        setOpt(CURLOPT_HTTPHEADER, headers);
    }
    
    /********
    * do it *
    ********/
    CURLcode status = curl_easy_perform(conn);
    if(status != CURLE_OK) {
        std::string msg = "Error: ";
        msg += error_msg;
        throw URLException(msg);
    }
        
    
} // end of perform method

/*********************************************************************//**
*
*************************************************************************/
void URL::headerData(char *ptr, size_t size, size_t nmemb) {
    
    std::cout << "HEAD "<<ptr;
    
} // end of headerData callback method

    
/*********************************************************************//**
*
*************************************************************************/
void URL::bodyData(char *ptr, size_t size, size_t nmemb) {
    
    body += ptr;
    
} // end of bodyData callback method
    
/*********************************************************************//**
*
*************************************************************************/
void URL::escape(const std::string& orig, std::string& escaped) {
    
    std::ostringstream s;
    
    for(int i=0; i<orig.length(); ++i) {
        char c = orig[i];
        
        //std::cout <<i<<" c="<<c<<std::endl;
        
        if(isUnreserved(c)) s << c;
        else                s << '%'<< std::hex << std::setw(2)<<std::setfill('0')<<(int)c;
        
    }
    
    escaped = s.str();
    
    //std::cout << "escaped="<<escaped<<std::endl;
    
} // end of escape method
    
/*********************************************************************//**
*
*************************************************************************/
bool URL::isUnreserved(char c) {
    
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9') ||
           c == '-' || c == '_' || c == '.' || c == '~';
    
} // end of isUnreserved static method
    
/*********************************************************************//**
*
*************************************************************************/
void URL::unescape(const std::string& orig, std::string& unescaped) {
    
    unescaped.clear();
    
    int offset=0;
    while(offset<orig.length()) {
        
        char c = orig[offset++];
        if(c == '%') {
            /******************
            * escape sequence *
            ******************/
            if(offset+1>=orig.length()) {
                throw URLException("Truncated escape sequence");
            }
            
            
            std::istringstream in(orig.substr(offset, 2));
            
            int value;
            in >> std::hex >> value;
            c = value;
            
            //std::cout << "hex: "<<orig.substr(offset, 2)<<" "<<value<<" "<<c<<std::endl;
            
            offset += 2;
            
            
        } // end if it wa an escape sequence
        
        /*******************
        copy the character *
        *******************/
        unescaped += c;

        
        
    } // end of loop over characters
    
} // end of unescape method
    
/*********************************************************************//**
*
*************************************************************************/
void URL::decode(const std::string& string, 
                 std::map<std::string, std::string>& map) {
    
    map.clear();
    
    size_t pos=0;
    while(true) {
        /****************************
        * find the next & separator *
        ****************************/
        size_t end = string.find('&', pos);
        
        /*****************************************
        * pull out the current &-separated field *
        *****************************************/
        std::string field;
        if(end == std::string::npos) {
            /*************************
            * this is the last field *
            *************************/
            field = string.substr(pos);
            break;
            
        } else {
            /*********************
            * pull out the field *
            *********************/
            field = string.substr(pos, end-pos);
            pos = end+1;
        }
        
        /*************************
        * pull out the key=value *
        *************************/
        size_t equals = field.find('=');
        std::string key = field.substr(0, equals);
        
        std::string value;
        unescape(field.substr(equals+1), value);
        
        map[key] = value;


    } // end of loop over fields
    
} //end of decode method
    
