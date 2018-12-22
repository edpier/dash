#include "URL.h"

#include <iostream>
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
    
    
    /************
    * callbacks *
    ************/
    setOpt(CURLOPT_HEADERDATA, this);
    setOpt(CURLOPT_HEADERFUNCTION, (void*)header_callback);

    setOpt(CURLOPT_WRITEDATA, this);
    setOpt(CURLOPT_WRITEFUNCTION, (void*)body_callback);

    
    
} // end of constructor

    
/*********************************************************************************//**
*
*************************************************************************************/
URL::~URL() {
    
} // end of destructor
    
/*********************************************************************************//**
*
*************************************************************************************/
void URL::setURL(const std::string& url) {
    
    setOpt(CURLOPT_URL, const_cast<char*>(url.c_str()));
    
} // end of setURL method
    
/*********************************************************************************//**
*
*************************************************************************************/
void URL::go() {
    
    body.clear();
    curl_easy_perform(conn);
    
} // end of go method
    
/*********************************************************************************//**
*
*************************************************************************************/
const std::string& URL::getBody() const {
    
    return body; 
    
} // end of getBody method
    
/*********************************************************************************//**
*
*************************************************************************************/
bool URL::globalInit() {
    
    curl_global_init(CURL_GLOBAL_DEFAULT);
    

    
} // end of globalInit static method
    
/*********************************************************************************//**
*
*************************************************************************************/
void URL::setOpt(CURLoption option, const void* parameter) {
    
    CURLcode status = curl_easy_setopt(conn, option, parameter);
    if(status != CURLE_OK) {
        std::string msg = "Error: ";
        msg += error_msg;
        throw URLException(msg);
    }
        
    
} // end of setOpt method
    
/*********************************************************************************//**
*
*************************************************************************************/
void URL::headerData(char *ptr, size_t size, size_t nmemb) {
    
    std::cout << "header data"<<std::endl;
    std::cout << "size="<<size<<std::endl;
    
    std::cout << ptr<<std::endl;
} // end of headerData callback method

    
/*********************************************************************************//**
*
*************************************************************************************/
void URL::bodyData(char *ptr, size_t size, size_t nmemb) {
    
//     std::cout << "body data"<<std::endl;
//     std::cout << "size="<<size<<std::endl;
//     
//     std::cout << ptr<<std::endl;
    
    body += ptr;
    
} // end of bodyData callback method
