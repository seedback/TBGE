#ifndef TBGE_GAME_OBJECT_GAME_OBJECT_WITH_COMMANDS_GAME_OBJECT_WITH_COMMANDS_H_
#define TBGE_GAME_OBJECT_GAME_OBJECT_WITH_COMMANDS_GAME_OBJECT_WITH_COMMANDS_H_

#include <string>
#include <vector>

#include "src/game_object/game_object.h"
#include "src/command/command.h"

namespace tbge {
class GameObjectWithCommands : public GameObject {
 public:
  // Constructors
  GameObjectWithCommands();
  GameObjectWithCommands(const std::string& name,
                         GameObject* parent = nullptr,
                         const std::vector<GameObject*> children = {nullptr});
  GameObjectWithCommands(const std::string& name,
                         const std::vector<std::string> descriptors,
                         const std::vector<Command> commands = {},
                         GameObject* parent = nullptr,
                         const std::vector<GameObject*> children = {nullptr});
  GameObjectWithCommands(const std::string& name,
                         const std::vector<GameObject*> children);
  GameObjectWithCommands(const GameObjectWithCommands& game_object_with_commands);

  // Destructors
  ~GameObjectWithCommands();

  // Accessors
  const std::vector<Command> getCommands() const;
  const std::vector<std::string> getDescriptors() const;

  // Queries
  const bool isDescribed(const std::vector<std::string> descriptors) const;

  // Mutators
  GameObjectWithCommands& setCommands(const std::vector<Command> commands);
  GameObjectWithCommands& setDescriptors(const std::vector<std::string> descriptors);
  GameObjectWithCommands& addCommand(const Command command);
  GameObjectWithCommands& addDescriptor(const std::string descriptor);
  GameObjectWithCommands& removeCommand(const Command command);
  GameObjectWithCommands& removeDescriptor(const std::string descriptor);

  // Commands
  void executeCommand(const std::string command_word,
                      const std::vector<std::string> arguments) const;

  // Protected
  static constexpr const char* CLASS_NAME = "GameObjectWithCommands";

 private:
  std::vector<Command> commands_;
  std::vector<std::string> descriptors_;
};
}  // namespace tbge

#endif  // TBGE_GAME_OBJECT_GAME_OBJECT_WITH_COMMANDS_GAME_OBJECT_WITH_COMMANDS_H_
