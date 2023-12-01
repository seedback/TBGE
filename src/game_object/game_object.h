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

#include "src/component/component.h"

namespace tbge {
/**
 * @file game_object.h
 * @brief Defines the GameObject class.
 */

/**
 * @class GameObject
 * @brief Represents a game object in the game engine.
 *
 * The GameObject class provides functionality for creating and managing game
 * objects.
 * It allows setting and getting the name, parent, children, and components of
 * a game object.
 * The class also provides methods for adding and removing children,
 * components, and parent.
 * Additionally, it provides queries to check if a game object has children,
 * parent, or a specific child.
 */

class Component; // Forward declaration of Component class

class GameObject {
 public:
  /**
   * @brief Default constructor for the GameObject class.
   *
   * @details This constructor will create a GameObject with a unique name
   *          based on its @a id_ and @a CLASS_NAME.
   *          This constructor will also register the GameObject with the
   *          global::Global singleton.
   */
  GameObject();

  /**
   * @brief Constructor for the GameObject class with a specified name, parent,
   *        and children.
   * 
   * @details If @a name is empty, the name will be set to @a CLASS_NAME + "_"
   *          + @a id_.
   *          As with all constructors, this constructor will also register the
   *          GameObject with the global::Global singleton.
   *
   * @param name The name of the GameObject.
   * @param parent The parent GameObject, defaults to nullptr.
   * @param children The children GameObjects, defaults to an empty list.
   * 
   * @see setName() 
   * @see setParent()
   * @see setChildren()
   */
  GameObject(const std::string& name,
       GameObject* parent = nullptr,
       const std::vector<GameObject*> children = {});

  /**
   * @brief Constructor for the GameObject class with a specified name and
   *        children.
   * 
   * @details If @a name is empty, the name will be set to @a CLASS_NAME + "_"
   *          + @a id_.
   *          As with all constructors, this constructor will also register the
   *          GameObject with the global::Global singleton.
   *
   * @param name The name of the GameObject.
   * @param children The children GameObjects.
   */
  GameObject(const std::string& name, std::vector<GameObject*> children);

  /**
   * @brief Copy constructor for the GameObject class.
   *
   * @param game_object The GameObject to be copied.
   */
  GameObject(const GameObject& game_object);

  /**
   * @brief Destructor for the GameObject class.
   */
  ~GameObject();

  /**
   * @brief Get the ID of the GameObject.
   *
   * @return The ID of the GameObject.
   */
  int getId() const;

  /**
   * @brief Get the class name of the GameObject.
   *
   * @return The class name of the GameObject.
   */
  const std::string getClassName() const;

  /**
   * @brief Get the name of the GameObject.
   *
   * @return The name of the GameObject.
   */
  const std::string getName() const;

  /**
   * @brief Get the full name of the GameObject.
   *
   * @return The full name of the GameObject.
   */
  const std::string getFullName() const;

  /**
   * @brief Get the parent GameObject of the GameObject.
   *
   * @return The parent GameObject of the GameObject.
   */
  GameObject* getParent() const;

  /**
   * @brief Get the children GameObjects of the GameObject.
   *
   * @return The children GameObjects of the GameObject.
   */
  const std::vector<GameObject*> getChildren() const;

  /**
   * @brief Get the first component of the specified type attached to the
   *        GameObject.
   *
   * @tparam T The type of the component.
   * @return The component of the specified type attached to the GameObject,
   *         or nullptr if not found.
   */
  template <typename T>
  T* getComponent() const;

  /**
   * @brief Get all components of the specified type attached to the
   *        GameObject.
   *
   * @tparam T The type of the components.
   * @return A vector containing all components of the specified type attached
   *         to the GameObject.
   */
  template <typename T>
  const std::vector<T*> getComponents() const;

  /**
   * @brief Set the name of the GameObject.
   * 
   * @details If @a name is empty, the name will be set to @a CLASS_NAME + "_"
   *          + @a id_.
   *          This method will also update the full name of the GameObject.
   * 
   * @param name The name of the GameObject.
   * @return A reference to the modified GameObject.
   */
  GameObject& setName(const std::string& name);

  /**
   * @brief Set the parent GameObject of the GameObject.
   *
   * @param parent The new parent GameObject.
   * @return A reference to the modified GameObject.
   */
  GameObject& setParent(GameObject* parent);

  /**
   * @brief Remove the parent GameObject of the GameObject.
   *
   * @return A reference to the modified GameObject.
   */
  GameObject& removeParent();

  /**
   * @brief Set the children GameObjects of the GameObject.
   *
   * @param children The children GameObjects.
   * @return A reference to the modified GameObject.
   */
  GameObject& setChildren(const std::vector<GameObject*> children);

  /**
   * @brief Add a child GameObject to the GameObject.
   *
   * @param child The child GameObject to be added.
   * @return A reference to the modified GameObject.
   */
  GameObject& addChild(GameObject* child);

  /**
   * @brief Remove all children GameObjects from the GameObject.
   *
   * @return A reference to the modified GameObject.
   */
  GameObject& removeChildren();

  /**
   * @brief Remove a specific child GameObject from the GameObject.
   *
   * @param child The child GameObject to be removed.
   * @return A reference to the modified GameObject.
   */
  GameObject& removeChild(GameObject* child);

  /**
   * @brief Remove a child GameObject with the specified ID from the
   *        GameObject.
   *
   * @param id The ID of the child GameObject to be removed.
   * @return A reference to the modified GameObject.
   */
  GameObject& removeChild(const int id);

  /**
   * @brief Remove a child GameObject with the specified name from the
   *        GameObject.
   *
   * @param name The name of the child GameObject to be removed.
   * @return A reference to the modified GameObject.
   */
  GameObject& removeChild(const std::string& name);

  /**
   * @brief Add a component to the GameObject. And register the game object as
   *        the parent to the component.
   * 
   * @tparam T A subclass of Component.
   * @return A reference to the added component.
   */
  template <typename T>
  T& addComponent();

  /**
   * @brief Remove the first component of the specified type from the
   *        GameObject. And delete it.
   * 
   * @tparam T A subclass of Component.
   * @return A reference to the modified GameObject.
   */
  template <typename T>
  GameObject& removeComponent();

  /**
   * @brief Remove a specific component from the GameObject. And delete it.
   * 
   * @param component The component to remove.
   * @return A reference to the modified GameObject.
   */
  GameObject& removeComponent(Component* component);

  /**
   * @brief Remove all components of the specified type from the GameObject.
   *        And delete them.
   * 
   * @tparam T A subclass of Component.
   * @return A reference to the modified GameObject.
   */
  template <typename T>
  GameObject& removeComponents();

  /**
   * @brief Remove all components from the GameObject. And delete them.
   *
   * @return A reference to the modified GameObject.
   */
  GameObject& clearComponents();

  /**
   * @brief Check if the GameObject has any children.
   *
   * @return True if the GameObject has children, false otherwise.
   */
  const bool hasChildren() const;

  /**
   * @brief Check if the GameObject has a parent.
   *
   * @return True if the GameObject has a parent, false otherwise.
   */
  const bool hasParent() const;

  /**
   * @brief Check if the GameObject has a specific child GameObject.
   *
   * @param child The child GameObject to check.
   * @return True if the GameObject has the specified child, false otherwise.
   */
  const bool hasChild(const GameObject* child) const;

  /**
   * @brief Check if the GameObject has a child GameObject with the specified
   *        ID.
   *
   * @param id The ID of the child GameObject to check.
   * @return True if the GameObject has a child with the specified ID, false
   *         otherwise.
   */
  const bool hasChild(const int id) const;

  /**
   * @brief Check if the GameObject has a child GameObject with the specified
   *        name.
   *
   * @param name The name of the child GameObject to check.
   * @return True if the GameObject has a child with the specified name, false
   *         otherwise.
   */
  const bool hasChild(const std::string& name) const;

  /**
   * @brief Check if the GameObject has a component of the specified type.
   *
   * @tparam T The type of the component.
   * @return True if the GameObject has a component of the specified type,
   *         false otherwise.
   */
  template <typename T>
  const bool hasComponent() const;

  // const bool hasComponent(Component* component) const;

 protected:
  // The class name of the GameObject, mainly used for logging, and giving the
  // default name.
  const std::string CLASS_NAME = "GameObject";

  /**
   * @brief Connect the GameObject to a parent GameObject.
   *
   * @param parent The parent GameObject to connect to.
   * @return A reference to the modified GameObject.
   */
  GameObject& connectParent(GameObject* parent);

  /**
   * @brief Disconnect the GameObject from its parent GameObject.
   *
   * @return A reference to the modified GameObject.
   */
  GameObject& disconnectParent();

  /**
   * @brief Connect a child GameObject to the GameObject.
   *
   * @param child The child GameObject to connect.
   * @return A reference to the modified GameObject.
   */
  GameObject& connectChild(GameObject* child);

  /**
   * @brief Disconnect a child GameObject from the GameObject.
   *
   * @param child The child GameObject to disconnect.
   * @return A reference to the modified GameObject.
   */
  GameObject& disconnectChild(GameObject* child);

  /**
   * @brief Set the ID of the GameObject.
   * 
   * @note This method should only be called in the constructor.
   */
  void setId();

  /**
   * @brief Update the full name of the GameObject.
   */
  void updateFullName();

 private:
  // Attributes
  int id_ = -1; // The ID of the GameObject
  std::string name_ = "UNNAMED"; // The name of the GameObject
  std::string full_name_ = "UNNAMED"; // The full name of the GameObject
  GameObject* parent_ = nullptr; // The parent GameObject
  // The children GameObjects
  std::vector<GameObject*> children_ = std::vector<GameObject*>();
  // The components attached to the GameObject
  std::vector<Component*> components_ = std::vector<Component*>();
};
}  // namespace tbge

#endif  // TBGE_GAME_OBJECT_GAME_OBJECT_H_

// FILEPATH: src/game_object/game_object.h
