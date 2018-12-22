#include "URLException.h"

    
/*********************************************************************************//**
*
*************************************************************************************/
URLException::URLException(const std::string& message) 
            : std::runtime_error(message) {
    
} // end of constructor
