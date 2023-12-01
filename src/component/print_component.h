#ifndef TBGE_COMPONENT_PRINT_H
#define TBGE_COMPONENT_PRINT_H

#include "src/component/component.h"

#include <iostream>
#include <string>
#include <initializer_list>

#include "src/game_object/game_object.h"

namespace tbge { 
class PrintComponent : public Component{
 public:
  // Constructors
  PrintComponent(GameObject* parent) : Component(parent) {};
  PrintComponent(const PrintComponent& print) : Component(print) {};

  // Destructors
  ~PrintComponent();

  // Actions
  template<typename... Args>
    void print(Args... args) const {
      // Convert the variadic template arguments to a std::initializer_list
      std::initializer_list<std::string> argsList = {args...};

      // Iterate over the list and print each argument on a new line
      for (const auto& arg : argsList) {
        std::cout << arg << std::endl;
      }
    }
};
}  // namespace tbge

#endif  // TBGE_COMPONENT_PRINT_H