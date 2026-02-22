#ifndef TBGE_SYSTEMS_LOCATION_CONTROLLER_H_
#define TBGE_SYSTEMS_LOCATION_CONTROLLER_H_

#include <string>
#include <vector>

#include "src/components/location_component.h"
#include "src/ecs/ecs.h"

namespace tbge {
class LocationController : ecs::System {
 public:
  void set_current_location(const ecs::Entity);
  ecs::Entity get_current_location() const;

  ecs::Entity get_location(const std::string);
  std::vector<ecs::Entity> get_child_locations(ecs::Entity) const;

 private:
  bool check_parent_tree(std::vector<std::string>, ecs::Entity) const;
  ecs::Entity current_location_;
};
}  // namespace tbge

#endif  // TBGE_SYSTEMS_LOCATION_CONTROLLER_H_