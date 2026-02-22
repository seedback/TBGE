#include "src/systems/exit_controller.h"

#include "absl/log/log.h"
#include "src/components/exit_component.h"
#include "src/components/lock_component.h"
#include "src/ecs/ecs.h"
#include "src/systems/location_controller.h"
#include "src/terminal/terminal.h"

namespace tbge {
extern ecs::Coordinator g_coordinator;
void ExitController::useExit(const ecs::Entity exit) const {
  if (!g_coordinator.HasComponent<ExitComponent>(exit)) {
    LOG(WARNING) << "Failed to use Exit; Entity " << exit
                 << " does not have an ExitComponent.";
  }

  if (g_coordinator.HasComponent<LockComponent>(exit)) {
    LockComponent lock_component =
        g_coordinator.GetComponent<LockComponent>(exit);
    if (lock_component.is_locked()) {
      tbge::terminal::UnicodePrint(lock_component.get_locked_description());
    }
  }

  ExitComponent exit_component =
      g_coordinator.GetComponent<ExitComponent>(exit);
  g_coordinator.GetSystem<LocationController>()->set_current_location(
      exit_component.get_target());
  // TODO: Create a tbge::print function that parses custom string codes and
  // prints them using UnicodePrint()
  tbge::terminal::UnicodePrint(exit_component.get_use_description());
}
}  // namespace tbge