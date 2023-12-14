
#ifndef TBGE_COMPONENT_COMPONENT_H
#define TBGE_COMPONENT_COMPONENT_H

#include <string>
#include <vector>

#include <iostream>

namespace tbge {
class Component {
 public:
  // Public
  // Friend classes
  friend class ComponentTest; // For the test suite
  // Constructors
  /**
   * @brief Constructs the root component
   * 
   * @throw std::runtime_error if called to construct a non-root component
  */
  Component();

  /**
   * @brief Constructs a component with a parent
   * 
   * @param parent The parent component
   * @throw std::runtime_error if parent is nullptr
  */
  Component(Component* parent);

  /**
   * @brief Copy constructor
   * 
   * @note This assigns a new id to the component
   * 
   * @param component The component to copy
  */
  Component(const Component& component);

  // Destructors
  ~Component();

  // Accessors
  static Component* getRoot();
  unsigned long long getId() const;
  const Component* getParent() const;
  Component* getComponent(unsigned long long component_id) const;
  template <typename T = void> Component* getComponent() const;
  std::vector<Component*> getComponents(
      std::vector<unsigned long long> component_ids,
      bool fileter_invalid_ids = true) const;
  template <typename T = void> std::vector<Component*>
      getComponents() const;

  // Mutators
  bool setParent(Component* parent);
  template <typename T> Component* addComponent();
  Component* addComponent(Component* component);
  template <typename T = void> bool removeComponent();
  bool removeComponent(unsigned long long component_id);
  bool removeComponent(Component* component);
  template <typename T> bool removeComponents();
  bool removeComponents(std::vector<unsigned long long> component_ids);
  bool removeComponents(std::vector<Component*> children);

  // Queries
  bool isDescendantOf(const Component* component) const;

  std::string dbgToString(int num_indent = 0) const;

 protected:
  void setId();
  bool registerComponent(Component* component);
  bool unregisterComponent(Component* component);
  bool registerParent(Component* parent);

  virtual Component* copy() const;

 private:
  // Private
  // Constants
  static const unsigned long long kRootId = 1;
  // Variables
  static Component* root_;
  static unsigned long long id_counter_;
  unsigned long long id_ = kRootId;
  Component* parent_ = nullptr;
  std::vector<Component*> components_ = {};
};  // class Component

  // Template definitions
  template <typename T>
  Component* Component::getComponent() const {
    // TODO: When logging system is in place make a warning if a non-component
    // type is passed in
    if (std::is_same<T, void>::value) {
      return components_.front();
    }
    // Traverse components_ to find a component component of type T
    for (auto component : components_) {
      if (typeid(*component) == typeid(T)) {
        return component;
      }
    }
    return nullptr;
  }

  template <typename T>
  std::vector<Component*> Component::getComponents() const {
    // TODO: When logging system is in place make a warning if a non-component
    // type is passed in
    if (std::is_same<T, void>::value) {
      return components_;
    }
    // A temporary vector to store all components that are of type T
    std::vector<Component*> components;
    // Traverse components_ to find components of type T
    // and add them to the temporary vector
    for (auto component : components_) {
      if (typeid(*component) == typeid(T)) {
        components.push_back(component);
      }
    }
    return components;
  }

  template <typename T> Component* Component::addComponent() {
    // Enusres that T is a component subclass
    if (! std::is_base_of<Component, T>::value) {
      return nullptr;
    }
    // Create a new component of type T
    Component* new_component = new T(this);
    return new_component;
  }

  template <typename T>
  bool Component::removeComponent() {
    // TODO: When logging system is in place make a warning if a non-component
    // type is passed in
    Component* component = nullptr;

    // If T is void, component should be the first component in components_
    if (std::is_same<T, void>::value) {
      component = components_.front();
    } else {
      // Traverse components_ to find a component of type T
      for (auto current_component : components_) {
        if (typeid(*current_component) == typeid(T)) {
          component = current_component;
          break;
        }
      }
    }

    // If no component of type T was not found, return false
    if(component == nullptr) {
      return false;
    }

    // Remove the component from components_ and delete it, return true
    unregisterComponent(component);
    delete component;
    return true;
  }

  template <typename T>
  bool Component::removeComponents() {
    // TODO: When logging system is in place make a warning if a non-component
    // type is passed in
    // Temporary variable to store whether or not at least one
    // component was removed
    bool hasRemovedAtLeastOneComponent = false;
    // Repeats until no components of type T are left
    while (true) {
      // If at least one component of type T was removed,
      // the function should return true
      if (removeComponent<T>() == true) {
        hasRemovedAtLeastOneComponent = true;
      // If no components of type T were removed, stop repeating.
      } else {
        break;
      }
    }
    // If at least one component of type T was removed,
    // hasRemovedAtLeastOneComponent will be true.
    // Otherwise, hasRemovedAtLeastOneComponent will be false
    return hasRemovedAtLeastOneComponent;
  }

}  // namespace tbge

#endif  // TBGE_COMPONENT_COMPONENT_H
