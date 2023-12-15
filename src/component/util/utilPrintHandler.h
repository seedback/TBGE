#ifndef TBGE_COMPONENT_UTIL_UTIL_PRINT_H_ANDLER_H_
#define TBGE_COMPONENT_UTIL_UTIL_PRINT_H_ANDLER_H_

#include "../component.h"

namespace tbge {
class UtilPrintHandler : Component {
 public:
  // Public
  // Friend classes
  friend class UtilPrintHandlerTest; // For the test suite

  template <typename... Args>
  void print(Args... args) const;

  template <typename T, typename... Args>
  void print(T t, Args... args) const;


 private: 
  
};
} // namespace tbge

#endif // TBGE_COMPONENT_UTIL_UTIL_PRINT_H_ANDLER_H_