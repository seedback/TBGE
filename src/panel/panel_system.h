#ifndef TBGE_SRC_PANEL_PANEL_SYSTEM_H_
#define TBGE_SRC_PANEL_PANEL_SYSTEM_H_

#include <set>

#include "src/ecs/ecs.h"
#include "src/panel/panel.h"

extern ECS::Coordinator<> gCoordinator;

namespace panel {

template <typename Context = ECS::Context<>>
class PanelSystem : public ECS::System<Context> {
 public:
  PanelSystem();

  void Redraw();

  // PanelSystem<Context>& add_entity(typename Context::Entity entity);
  // PanelSystem<Context>& remove_entity(typename Context::Entity entity);

 private:
  struct CompareZList {
    bool operator()(const typename Context::Entity& a,
                    const typename Context::Entity& b) const {
      auto& panel_a = gCoordinator.GetComponent<panel::Panel<Context>>(a);
      auto& panel_b = gCoordinator.GetComponent<panel::Panel<Context>>(b);
      
      auto z_a = panel_a.get_z();
      auto z_b = panel_b.get_z();
      
      if (z_a != z_b) {
        return z_a > z_b;  // Higher z on top
      }
      
      return a < b;  // Tiebreaker: stable sort by entity ID
    }
  };

  std::set<typename Context::Entity, CompareZList> z_list_;
};
}  // namespace panel

#include "src/panel/panel_system.tcc"
#endif  // TBGE_SRC_PANEL_PANEL_SYSTEM_H_