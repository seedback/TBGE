#ifndef TBGE_SRC_PANEL_PANEL_SYSTEM_TCC_
#define TBGE_SRC_PANEL_PANEL_SYSTEM_TCC_

#include "src/ecs/ecs.h"
#include "src/panel/panel.h"
#include "src/panel/panel_system.h"

extern ECS::Coordinator<> gCoordinator;

namespace panel {

template <typename Context>
PanelSystem<Context>::PanelSystem() {
  // z_list_ will be populated dynamically when Redraw() is called
}

template <typename Context>
void PanelSystem<Context>::Redraw() {
  std::set<typename Context::Entity> entities = this->get_entities();
  z_list_.clear();
  z_list_.insert(entities.begin(), entities.end());
  
  for (typename Context::Entity entity : z_list_) {
    panel::Panel<Context>& panel =
        gCoordinator.GetComponent<panel::Panel<Context>>(entity);
    panel.Draw();
  }
}
}  // namespace panel

#endif  // TBGE_SRC_PANEL_PANEL_SYSTEM_TCC_