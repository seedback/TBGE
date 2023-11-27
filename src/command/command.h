#ifndef TBGE_SRC_COMMAND_COMMAND_H_
#define TBGE_SRC_COMMAND_COMMAND_H_

#include <string>
#include <vector>

#include "src/command/command_action/command_action.h"

namespace tbge {
class Command {
 public:
  Command(const std::string& command_word, CommandAction* command_action);
  bool operator==(const Command& command) const;
  ~Command();

  const std::string getCommandWord() const;

  const void execute(std::vector<std::string>arguments) const;

 private:
  std::string command_word_;
  CommandAction* command_action_;
};
}  // namespace tbge

#endif  // TBGE_SRC_COMMAND_COMMAND_H_
