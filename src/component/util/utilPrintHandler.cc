#include "utilPrintHandler.h"

#include <iostream>
#include <string>
#include <vector>

namespace tbge {

template <typename... Args>
void UtilPrintHandler::print(Args... args) const {
  print(args...);
}

template <typename T, typename... Args>
void UtilPrintHandler::print(T t, Args... args) const {
  // Check if t is a string
  if (std::is_same<T, std::string>::value) {
    std::cout << t;
  }

  #ifdef TBGE_DEBUG
  else {
    std::cout << "UtilPrintHandler::print: t is not a string" << std::endl;
  }
  #endif

  print(args...);
}

} // namespace tbge
