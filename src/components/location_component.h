#ifndef TBGE_COMPONENTS_LOCATION_MODEL_H_
#define TBGE_COMPONENTS_LOCATION_MODEL_H_

#include <string>
#include <vector>

#include "absl/log/check.h"
#include "src/ecs/ecs.h"

namespace tbge {
extern ecs::Coordinator g_coordinator;

class LocationComponent : ecs::Component {
 public:
  LocationComponent(std::string name, std::string description, ecs::Entity parent) {
    set_name(name);
  }

  void set_name(const std::string& name) { name_ = name; }
  const std::string& get_name() const { return name_; }

  void set_description(const std::string& description) {
    description_ = description;
  }
  const std::string& get_description() const { return description_; }

  void set_parent(const ecs::Entity parent) {
    CHECK(g_coordinator.HasComponent<LocationComponent>(parent))
        << "Failed to set parent to LocationComponent on Entity "
        << get_entity_id() << "; Entity " << parent
        << " does not have a LocationComponent.";
    parent_ = parent;
  }
  ecs::Entity get_parent() const {
    CHECK(g_coordinator.HasComponent<LocationComponent>(parent_))
        << "Failed to get parent to LocationComponent on Entity "
        << get_entity_id() << "; Entity " << parent_
        << " does no longer have a LocationComponent.";
    return parent_;
  }

 private:
  std::string name_;
  std::string description_;
  ecs::Entity parent_;
};
}  // namespace tbge

#endif  // TBGE_COMPONENTS_LOCATION_MODEL_H_