#ifndef TBGE_SYSTEMS_EXIT_CONTROLLER_H_
#define TBGE_SYSTEMS_EXIT_CONTROLLER_H_

#include "src/components/exit_component.h"
#include "src/components/location_component.h"
#include "src/ecs/ecs.h"

namespace tbge {
class ExitController : ecs::System {
 public:
  void useExit(const ecs::Entity) const;

 private:
};
}  // namespace tbge

#endif  // TBGE_SYSTEMS_EXIT_CONTROLLER_H_