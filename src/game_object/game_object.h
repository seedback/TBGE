/*
* _____________________________
*    _____ ____   ____ _____   
*   |_   _| __ ) / ___| ____|  
*     | | |  _ \| |  _|  _|    
*     | | | |_) | |_| | |___   
*     |_| |____/ \____|_____|  
* _____________________________
* game_object.h
*/

#ifndef TBGE_GAME_OBJECT_GAME_OBJECT_H_
#define TBGE_GAME_OBJECT_GAME_OBJECT_H_

#include <string>
#include <vector>

namespace tbge {
class GameObject {
 public:
  // Constructors
  GameObject();
  GameObject(const std::string& name,
             GameObject* parent = nullptr,
             const std::vector<GameObject*> children = {nullptr});
  GameObject(const std::string& name, std::vector<GameObject*> children);
  GameObject(const GameObject& game_object);

  // Destructors
  ~GameObject();

  // Accessors
  int getId() const;
  const std::string getClassName() const;
  const std::string getName() const;
  const std::string getFullName() const;
  GameObject* getParent() const;
  const std::vector<GameObject*> getChildren() const;

  // Queries
  const bool hasChildren() const;
  const bool hasParent() const;
  const bool hasChild(const GameObject* child) const;
  const bool hasChild(const int id) const;
  const bool hasChild(const std::string& name) const;

  // Mutators
  GameObject& setName(const std::string& name);
  GameObject& setParent(GameObject* parent);
  GameObject& removeParent();
  GameObject& setChildren(const std::vector<GameObject*> children);
  GameObject& addChild( GameObject* child);
  GameObject& removeChildren();
  GameObject& removeChild(GameObject* child);
  GameObject& removeChild(const int id);
  GameObject& removeChild(const std::string& name);

 protected:
  // Constants
  static constexpr const char* CLASS_NAME = "GameObject";

  // Mutators
  GameObject& connectParent(GameObject* parent);
  GameObject& disconnectParent();
  GameObject& connectChild(GameObject* child);
  GameObject& disconnectChild(GameObject* child);
  void setId();
  void updateFullName();

 private:
  // Attributes
  int id_ = -1;
  std::string name_ = "UNNAMED";
  std::string full_name_ = "UNNAMED";
  GameObject* parent_ = nullptr;
  std::vector<GameObject*> children_ = std::vector<GameObject*>();
};
}  // namespace tbge

#endif  // TBGE_GAME_OBJECT_GAME_OBJECT_H_

// FILEPATH: src/game_object/game_object.h
