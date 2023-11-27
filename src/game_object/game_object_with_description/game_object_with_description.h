#ifndef TBGE_GAME_OBJECT_GAME_OBJECT_WITH_DESCRIPTION_GAME_OBJECT_WITH_DESCRIPTION_H_
#define TBGE_GAME_OBJECT_GAME_OBJECT_WITH_DESCRIPTION_GAME_OBJECT_WITH_DESCRIPTION_H_

#include "src/game_object/game_object_with_commands/game_object_with_commands.h"

#include <string>

namespace tbge {
class GameObjectWithDescription: public GameObjectWithCommands {
 public:
  // Constructors
  GameObjectWithDescription();
  GameObjectWithDescription(const std::string& name,
                            GameObject* parent = nullptr,
                            const std::vector<GameObject*> children = {nullptr});

  GameObjectWithDescription(const std::string& name,
                            const std::vector<GameObject*> children);

  GameObjectWithDescription(const std::string& name,
                            const std::vector<std::string> descriptors,
                            const std::vector<Command> commands = {},
                            GameObject* parent = nullptr,
                            const std::vector<GameObject*> children = {nullptr});

  GameObjectWithDescription(const std::string& name,
                            const std::string description,
                            const std::string short_description,
                            const std::vector<std::string> descriptors,
                            const std::vector<Command> commands,
                            GameObject* parent,
                            const std::vector<GameObject*> children);
                            
  GameObjectWithDescription(const GameObjectWithDescription& game_object_with_description);
  
  // Destructor
  ~GameObjectWithDescription();

  // Accessors
  const std::string getDescription() const;
  const std::string getShortDescription() const;

  // Mutators
  void setDescription(const std::string& description);
  void setShortDescription(const std::string& short_description);

  // Commands
  void printDescription() const;
  void printShortDescription() const;

 private:
  std::string description_ = "";
  std::string short_description_ = "";
};
} // namespace tbge

#endif  // TBGE_GAME_OBJECT_GAME_OBJECT_WITH_DESCRIPTION_GAME_OBJECT_WITH_DESCRIPTION_H_
