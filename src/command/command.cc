#include "command.h"

namespace tbge {

Command::Command(const std::string& command_word, CommandAction* command_action)
    : command_word_(command_word), command_action_(command_action) {}

bool Command::operator==(const Command& command) const {
  return command_word_ == command.command_word_ && command_action_ == command.command_action_;
}

Command::~Command() {}

const std::string Command::getCommandWord() const {
  return command_word_;
}

const void Command::execute(std::vector<std::string>arguments) const {
  command_action_->execute(arguments);
}

}  // namespace tbge
