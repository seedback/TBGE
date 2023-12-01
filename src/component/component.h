
#ifndef TBGE_COMPONENT_COMPONENT_H
#define TBGE_COMPONENT_COMPONENT_H

#include "src/game_object/game_object.h"

#include <vector>

namespace tbge {
class GameObject; // Forward declaration
class Component {
 public:
  // Public
  // Constructors
  Component();
  Component(Component* parent);
  Component(const Component& component);

  // Destructors
  virtual ~Component() = default;

  // Mutators
  template <typename T> bool removeChild();
  bool removeChild(unsigned long long child_id);
  bool removeChild(Component* child);
  template <typename T> bool removeChildren();
  bool removeChildren(std::vector<unsigned long long> children_ids);
  bool removeChildren(std::vector<Component*> children);

  // Accessors
  Component* getRoot();
  unsigned long long getId() const;
  const Component* getParent() const;
  template <typename T = void> Component* getChild() const;
  Component* getChild(unsigned long long child_id) const;
  template <typename T = void> std::vector<Component*> getChildren() const;
  std::vector<Component*> getChildren(
      std::vector<unsigned long long> children_ids) const;
      
 protected:
  void setId();
  void addChild(Component* child);
  
 private:
  // Variables
  static Component* root_;
  unsigned long long id_;
  Component* parent_;
  std::vector<Component*> children_;
};  // class Component
}  // namespace tbge

#endif  // TBGE_COMPONENT_COMPONENT_H
