
#ifndef TBGE_COMPONENT_COMPONENT_H
#define TBGE_COMPONENT_COMPONENT_H

#include <string>
#include <vector>

namespace tbge {
class Component {
 public:
  // Public
  // Friend classes
  friend class ComponentTest;
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
  template <typename T> Component* getComponent() const {
    // TODO: When logging system is in place make a warning if a non-component
    // type is passed in
    // Traverse components_ to find a component component of type T
    for (auto component : components_) {
      if (typeid(*component) == typeid(T)) {
        return component;
      }
    }
    return nullptr;
  }
  std::vector<Component*> getComponents(
      std::vector<unsigned long long> component_ids) const;
  template <typename T = void> std::vector<Component*> getComponents() const {
    if (std::is_same<T, void>::value) {
      return components_;
    }
    // TODO: When logging system is in place make a warning if a non-component
    // type is passed in
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

  // Mutators
  bool setParent(Component* parent);
  template <typename T> long long addComponent() {
    // Enusres that T is a component subclass
    if (! std::is_base_of<Component, T>::value) {
      return -1;
    }
    // Create a new component of type T
    Component* new_component = new T(this);
    return new_component->getId();
  }
  long long addComponent(Component* component);
  template <typename T = void> bool removeComponent() {
    // TODO: When logging system is in place make a warning if a non-component
    // type is passed in
    Component* component = nullptr;
    
    // Traverse components_ to find a component of type T
    for (auto current_component : components_) {
      if (typeid(*current_component) == typeid(T)) {
        component = current_component;
        break;
      }
    }

    // If T is void, component should be the first component in components_
    if (std::is_same<T, void>::value) {
      component = components_.front();
    }

    // If no component of type T was found, return false
    if(component == nullptr) {
      return false;
    }

    // Remove the component from components_ and delete it
    unregisterComponent(component);
    delete component;
    return true;
  }
  bool removeComponent(unsigned long long component_id);
  bool removeComponent(Component* component);
  template <typename T> bool removeComponents() {
    // TODO: When logging system is in place make a warning if a non-component
    // type is passed in
    // Temporary variable to store whether or not a component was removed
    bool removed = false;
    // Repeats until no components of type T are left
    while (true) {
      // If at least one component of type T was removed,
      // the function should return true
      if (removeComponent<T>() == true) {
        removed = true;
      // If no components of type T were removed, stop repeating.
      } else {
        break;
      }
    }
    // If at least one component of type T was removed, removed will be true
    // Otherwise, removed will be false
    return removed;
  }
  bool removeComponents(std::vector<long long> component_ids);
  bool removeComponents(std::vector<Component*> children);

  // Queries
  bool isDescendantOf(const Component* component) const;

  std::string dbgToString(int num_indent = 0) const;

 protected:
  void setId();
  void registerComponent(Component* component);
  void unregisterComponent(Component* component);
  void registerParent(Component* parent);

 private:
  // Variables
  static Component* root_;
  long long id_ = 0;
  static long long id_counter_;
  Component* parent_ = nullptr;
  std::vector<Component*> components_ = {};
};  // class Component
}  // namespace tbge

#endif  // TBGE_COMPONENT_COMPONENT_H
