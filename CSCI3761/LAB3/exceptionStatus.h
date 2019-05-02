#ifndef EXCEPTION_STATUS_H
#define EXCEPTION_STATUS_H


#include <string>

/** Exception_status
 * exception_status is used as a returned object that returns \n
 * 1) If an error occured \n
 * 2) What the error that occured was \n
 * 3) Optional count that says where in the process the error occured. */
struct exception_status {
  std::string status;
  bool error = false;
  int which;

  /** Set's the object in the event of a badcall
   *@param s error code
   *@return *this  - useful for aborting on the same line as call */
  exception_status &badCall(std::string s) {
    this->error = true;
    this->status = s;
    return *this;
  }

  /** Get the reason for the error. Similar in all respects to std::exception.*/
  std::string what() { return this->status; }

  exception_status() : status(""), error(false), which(0) {}
};


#endif
