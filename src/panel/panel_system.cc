#include <conio.h>
#include <algorithm>
#include <set>

#include "src/ecs/ecs.h"
#include "src/panel/content/panel_content_system.h"
#include "src/panel/panel.h"
#include "src/panel/panel_system.h"

extern ECS::Coordinator gCoordinator;

namespace panel {

void DebugPrintZIndices() {
  std::shared_ptr<panel::PanelSystem> system =
      gCoordinator.GetSystem<panel::PanelSystem>();
  std::set<ECS::Entity> entities = system->get_entities();
  int i = 0;
  for (auto entity : entities) {
    tbge::tui::SetCursorPosition(0, i + 20);
    std::cout << "Entity " << entity << " Z: "
              << gCoordinator.GetComponent<panel::Panel>(entity).get_z_index()
              << std::endl;
    i++;
  }
}

struct CompareZList {
  bool operator()(const ECS::Entity& a,
                  const ECS::Entity& b) const {
    auto& panel_a = gCoordinator.GetComponent<panel::Panel>(a);
    auto& panel_b = gCoordinator.GetComponent<panel::Panel>(b);

    auto z_a = panel_a.get_z_index();
    auto z_b = panel_b.get_z_index();

    if (z_a != z_b) {
      return z_a > z_b;  // Higher z on top
    }

    return a < b;  // Tiebreaker: stable sort by entity ID
  }
};

PanelSystem::PanelSystem() {
  // z_list_ will be populated dynamically when Redraw() is called
}

void PanelSystem::Redraw() {
  std::sort(z_list_.begin(), z_list_.end(), CompareZList());
  for (ECS::Entity entity : z_list_) {
    panel::Panel& panel =
        gCoordinator.GetComponent<panel::Panel>(entity);
    panel.Draw();
  }
}

void PanelSystem::RotatePanelZs() {
  if (z_list_.empty()) return;
  int bottom_z =
      gCoordinator.GetComponent<panel::Panel>(z_list_.front())
          .get_z_index();
  gCoordinator.GetComponent<panel::Panel>(z_list_.back())
      .set_z_index(bottom_z + 1);

  std::sort(z_list_.begin(), z_list_.end(), CompareZList());

  // Subtract 1 from all indices to prevent them from growing too high
  if (gCoordinator.GetComponent<panel::Panel>(z_list_.back())
          .get_z_index() > 0) {
    for (auto entity : z_list_) {
      auto& panel = gCoordinator.GetComponent<panel::Panel>(entity);
      panel.set_z_index(panel.get_z_index() - 1);
    }
  }
}

void PanelSystem::PutEntityToFront(ECS::Entity entity) {
  if (z_list_.empty()) return;
  if (z_list_.back() == entity) return;

  int last_z = gCoordinator.GetComponent<panel::Panel>(z_list_.back())
                   .get_z_index();
  gCoordinator.GetComponent<panel::Panel>(entity).set_z_index(last_z -
                                                                       1);

  // Subtract 1 from all indices to prevent them from growing too high
  if (gCoordinator.GetComponent<panel::Panel>(z_list_.back())
          .get_z_index() < z_list_.size()) {
    for (auto entity : z_list_) {
      auto& panel = gCoordinator.GetComponent<panel::Panel>(entity);
      panel.set_z_index(panel.get_z_index() + 1);
    }
  }

  std::sort(z_list_.begin(), z_list_.end(), CompareZList());
}

PanelSystem& PanelSystem::add_entity(
    ECS::Entity entity) {
  // Prevent duplicates - don't add if already present
  ECS::System::add_entity(entity);
  z_list_.push_back(entity);
  std::sort(z_list_.begin(), z_list_.end(), CompareZList());
  return *this;
}

PanelSystem& PanelSystem::remove_entity(
    ECS::Entity entity) {
  ECS::System::remove_entity(entity);
  z_list_.erase(std::find(z_list_.begin(), z_list_.end(), entity));
  return *this;
}

}  // namespace panel
