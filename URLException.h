#ifndef URL_EXCEPTION_H
#define URL_EXCEPTION_H

#include <stdexcept>
#include <string>

class URLException : public std::runtime_error {
    
public:
    URLException(const std::string& message);
    virtual ~URLException() {}
    
}; // end of URLException class

#endif
