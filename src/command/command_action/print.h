#ifndef TBGE_COMMAND_COMMAND_ACTION_PRINT_H_
#define TBGE_COMMAND_COMMAND_ACTION_PRINT_H_

#include <string>
#include <vector>
#include <iostream>

#include "src/command/command_action/command_action.h"

namespace tbge {
class PrintCommandAction : public virtual CommandAction {
 public:
  PrintCommandAction() {}
  ~PrintCommandAction() {}

 protected:
  virtual void execute(std::vector<std::string>& arguments) override {
    for (auto argument : arguments) {
      std::cout << argument << std::endl;
    }
  }

 private:
};
}  // namespace tbge

#endif // TBGE_COMMAND_COMMAND_ACTION_PRINT_H_
