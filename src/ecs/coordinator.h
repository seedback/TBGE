#ifndef TBGE_SRC_ECS_COORDINATOR_H_
#define TBGE_SRC_ECS_COORDINATOR_H_

#include <memory>

#include "src/ecs/component_manager.h"
#include "src/ecs/context.h"
#include "src/ecs/entity_manager.h"
#include "src/ecs/system_manager.h"

namespace ECS {

/**
 * @class Coordinator
 * @brief Central class for managing entities, components, and systems in
 * this ECS (Entity Component System) architecture.
 * 
 * @tparam Context The Context that holds configuration data and data types.
 * 
 * @details
 * The Coordinator class provides a unified interface for creating and
 * destroying entities, registering and managing components, and handling
 * systems and their signatures. It acts as the main entry point for
 * interacting with the ECS framework.
 */
template <typename Context = Context<>>
class Coordinator {
 public:
  using Entity = typename Context::Entity;
  using ComponentType = typename Context::ComponentType;
  using Signature = typename Context::Signature;

  /**
   * @brief Constructs a Coordinator object and initializes its internal state.
   *
   * @details
   * The constructor calls the Init() method to set up the necessary components
   * and systems required for the Coordinator to function properly.
   */
  Coordinator();

  // #####   Entity methods   #####
  /**
   * @brief Creates a new entity within the ECS (Entity Component System).
   *
   * @return The newly created entity identifier.
   */
  Entity CreateEntity();

  /**
   * @brief Destroys the specified entity and removes all associated components.
   *
   * @details
   * This function removes the entity from the ECS (Entity Component System) and
   * ensures that all components attached to the entity are properly cleaned up.
   * After calling this function, the entity will no longer exist within the
   * system.
   *
   * @param entity The entity to be destroyed.
   * @return Reference to the Coordinator for method chaining.
   */
  Coordinator<Context>& DestroyEntity(Entity entity);

  // #####   Component methods   #####
  /**
   * @brief Registers a new component type with the coordinator.
   *
   * @details
   * This function should be called to inform the coordinator about a new
   * component type that will be used in the ECS (Entity Component System). It
   * typically sets up internal data structures to manage the component type.
   *
   * @tparam T The type of the component to register.
   * @return Reference to the Coordinator instance for method chaining.
   */
  template <typename T>
  Coordinator<Context>& RegisterComponentType();

  /**
   * @brief Adds a component of type T to the specified entity.
   *
   * @details
   * Adds a component to the entity and updates the entity's signature.
   *
   * @tparam T The type of the component to add.
   * @param entity The entity to which the component will be added.
   * @param component The component instance to add to the entity.
   * @return Reference to the Coordinator for method chaining.
   */
  template <typename T>
  Coordinator<Context>& AddComponent(Entity entity, T component);

  /**
   * @brief Removes a component of type T from the specified entity.
   *
   * @details
   * Removes a component from the entity and updates the entity's signature.
   *
   * @tparam T The type of the component to remove.
   * @param entity The entity from which the component will be removed.
   * @return Reference to the Coordinator for method chaining.
   */
  template <typename T>
  Coordinator<Context>& RemoveComponent(Entity entity);

  /**
   * @brief Retrieves a reference to the component of type T associated with the
   * given entity.
   *
   * @tparam T The type of the component to retrieve.
   * @param entity The entity whose component is to be retrieved.
   * @return Reference to the component of type T associated with the specified
   * entity.
   * @throws std::out_of_range If the entity does not have a component of type
   * T.
   */
  template <typename T>
  T& GetComponent(Entity entity);

  /**
   * @brief Retrieves the unique ComponentType identifier for the specified
   * component type T.
   *
   * @tparam T The component type for which to obtain the ComponentType
   * identifier.
   * @return ComponentType The unique identifier associated with the component
   * type T.
   */
  template <typename T>
  ComponentType GetComponentType();

  // #####   System methods   #####
  /**
   * @brief Registers a new system of type T with the coordinator.
   *
   * @details
   * This function creates and registers a system of the specified type T,
   * and returns a shared pointer to the newly created system instance.
   *
   * @tparam T The type of the system to register. Must inherit from the base
   * System class.
   * @return std::shared_ptr<T> A shared pointer to the registered system
   * instance.
   *
   * @note If a system of type T is already registered, this function may return
   * the existing instance or create a new one, depending on the implementation.
   */
  template <typename T>
  std::shared_ptr<T> RegisterSystem();

  /**
   * @brief Sets the signature for a system of type T.
   *
   * @details
   * This method associates a specific entity-component signature with the
   * system of type T. The signature determines which entities the system will
   * operate on, based on the components they possess.
   *
   * @tparam T The type of the system for which the signature is being set.
   * @param signature The signature representing the required components for the
   * system.
   * @return Reference to the Coordinator to allow method chaining.
   */
  template <typename T>
  Coordinator<Context>& SetSystemSignature(Signature signature);

 private:
  /**
   * @brief Initializes the Coordinator instance.
   *
   * @details
   * This function sets up the necessary state and resources for the
   * Coordinator. It should be called before using any other Coordinator
   * functionality.
   *
   * @note This function is automatically called by the constructor.
   *
   * @return Reference to the initialized Coordinator instance.
   */
  Coordinator<Context>& Init();

#ifdef _DEBUG
  void debug_warning();
#endif

  Context config_;
  std::unique_ptr<ComponentManager<Context>> component_manager_;
  std::unique_ptr<EntityManager<Context>> entity_manager_;
  std::unique_ptr<SystemManager<Context>> system_manager_;
};

}  // namespace ECS

#include "src/ecs/coordinator.tcc"
#endif  // TBGE_SRC_ECS_COORDINATOR_H_