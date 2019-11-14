#ifndef MP4_EXCEPTION_H
#define MP4_EXCEPTION_H

#include <stdexcept>

class MP4Exception : public std::runtime_error {
 private:
 public:
  MP4Exception(const std::string& message);
  virtual ~MP4Exception() throw() {}

};  // end of MP4Exception class

#endif
