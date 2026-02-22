#include "src/systems/location_controller.h"

#include <string>
#include <vector>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/components/location_component.h"
#include "src/ecs/ecs.h"

namespace tbge {
extern ecs::Coordinator g_coordinator;
void LocationController::set_current_location(const ecs::Entity location) {
  CHECK(g_coordinator.HasComponent<LocationComponent>(location))
      << "Failed to set current_location on location_controller; Entity "
      << location << "does not have a LocationComponent.";

  current_location_ = location;
}

ecs::Entity LocationController::get_current_location() const {
  CHECK(g_coordinator.HasComponent<LocationComponent>(current_location_))
      << "Failed to get current_location on LocationController; Entity "
      << current_location_ << "does no longer have a LocationComponent.";

  return current_location_;
}

ecs::Entity LocationController::get_location(const std::string name) {
  // Split the name by '.' to get location hierarchy
  std::vector<std::string> path_parts;
  size_t start = 0;
  size_t end = name.find('.');

  while (end != std::string::npos) {
    path_parts.push_back(name.substr(start, end - start));
    start = end + 1;
    end = name.find('.', start);
  }
  path_parts.push_back(name.substr(start));

  for (ecs::Entity entity : get_entities()) {
    LocationComponent location =
        g_coordinator.GetComponent<LocationComponent>(entity);
    if (check_parent_tree(path_parts, entity)) {
      return entity;
    }
  }

  LOG(FATAL) << "Could not find location " << name
             << "; no such location path exists.";
}

std::vector<ecs::Entity> LocationController::get_child_locations(ecs::Entity location) const {
  std::vector<ecs::Entity> child_locations;
  for (ecs::Entity entity : get_entities()) {
    if(g_coordinator.GetComponent<LocationComponent>(entity).get_parent() == location) {
      child_locations.push_back(entity);
    }
  }
  return child_locations;
}

bool LocationController::check_parent_tree(const std::vector<std::string> path,
                                           ecs::Entity entity) const {
  if (!g_coordinator.HasComponent<LocationComponent>(entity)) {
    return false;
  }
  LocationComponent location =
      g_coordinator.GetComponent<LocationComponent>(entity);
  if (path.back() == location.get_name()) {
    if (path.size() > 1) {
      std::vector<std::string> next_path = path;
      next_path.pop_back();
      return check_parent_tree(next_path, location.get_parent());
    }
    return true;
  }
  return false;
}
}  // namespace tbge