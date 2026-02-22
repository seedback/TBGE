#ifndef TBGE_COMPONENTS_EXIT_MODEL_H_
#define TBGE_COMPONENTS_EXIT_MODEL_H_

#include <string>

#include "absl/log/log.h"
#include "src/components/location_component.h"
#include "src/ecs/ecs.h"

namespace tbge {
extern ecs::Coordinator g_coordinator;

class ExitComponent {
 public:
  void set_description(std::string description) { description_ = description; }
  std::string get_description() { return description_; }

  void set_use_description(std::string use_description) {
    use_description_ = use_description;
  }
  std::string get_use_description() { return use_description_; }

  void set_location(ecs::Entity location) {
    if (!g_coordinator.HasComponent<LocationComponent>(location)) {
      LOG(WARNING) << "Failed to set exit location to entity " << location
                   << "; entity does not have a LocationComponent.";
    } else {
      location_ = location;
    }
  }
  ecs::Entity get_location() { return location_; }

  void set_target(ecs::Entity target) {
    if (!g_coordinator.HasComponent<LocationComponent>(target)) {
      LOG(WARNING) << "Failed to set exit target to entity " << target
                   << "; entity does not have a LocationComponent.";
    } else {
      target_ = target;
    }
  }
  ecs::Entity get_target() { return target_; }

 private:
  std::string description_;
  std::string use_description_;
  ecs::Entity location_;
  ecs::Entity target_;
};
}  // namespace tbge

#endif  // TBGE_COMPONENTS_EXIT_MODEL_H_