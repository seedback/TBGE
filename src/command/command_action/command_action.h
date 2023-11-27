#ifndef TBGE_COMMAND_COMMAND_ACTION_COMMAND_ACTION_H_
#define TBGE_COMMAND_COMMAND_ACTION_COMMAND_ACTION_H_

#include <string>
#include <vector>

namespace tbge {
class CommandAction {
 public:
  friend class Command;

  CommandAction() {}
  ~CommandAction() {}

 protected:
  virtual void execute(std::vector<std::string>& arguments) = 0;

 private:
  
};
}  // namespace tbge

#endif // TBGE_COMMAND_COMMAND_ACTION_COMMAND_ACTION_H_
