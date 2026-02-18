#ifndef TBGE_SRC_PANEL_PANEL_SYSTEM_H_
#define TBGE_SRC_PANEL_PANEL_SYSTEM_H_


#include <vector>

#include "src/ecs/ecs.h"
#include "src/panel/panel.h"

extern ECS::Coordinator gCoordinator;

namespace panel {

class PanelSystem : public ECS::System {
 public:
  PanelSystem();

  void Redraw();

  void RotatePanelZs();
  void PutEntityToFront(ECS::Entity);

  PanelSystem& add_entity(ECS::Entity);
  PanelSystem& remove_entity(ECS::Entity);

 private:
  std::vector<ECS::Entity> z_list_;
};
}  // namespace panel

#endif  // TBGE_SRC_PANEL_PANEL_SYSTEM_H_