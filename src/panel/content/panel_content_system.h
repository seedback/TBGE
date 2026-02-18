#ifndef SRC_PANEL_CONTENT_CONTENT_SYSTEM_H_
#define SRC_PANEL_CONTENT_CONTENT_SYSTEM_H_

#include <algorithm>
#include <iostream>

#include "src/ecs/ecs.h"
#include "src/panel/content/content.h"
#include "src/panel/panel.h"

extern ECS::Coordinator gCoordinator;

namespace panel {
class PanelContentSystem : public ECS::System {
 public:
  void ReconfigurePanels() {
    for (ECS::Entity entity : this->get_entities()) {
      panel::Content& content =
          gCoordinator.GetComponent<panel::Content>(entity);
      panel::Panel& panelComponent =
          gCoordinator.GetComponent<panel::Panel>(entity);

      unsigned int line_width = GetMaxLineWidth_(content);
      unsigned int num_lines = content.get_text().size();

      unsigned int new_x = std::max((unsigned int)panelComponent.get_size().x,
                                    line_width + (content.get_padding().x + 1) * 2);
      unsigned int new_y = std::max((unsigned int)panelComponent.get_size().y,
                                    num_lines + (content.get_padding().y + 1) * 2);

      panelComponent.set_size(new_x, new_y);
    }
  }

  void RedrawEntityContent(ECS::Entity entity) {
    if (!gCoordinator.EntityIsValidForSystem<PanelContentSystem>(
            entity)) {
      return;
    }

    Panel panelComponent =
        gCoordinator.GetComponent<Panel>(entity);
    Content panelContentComponent = gCoordinator.GetComponent<Content>(entity);

    for (int i = 0; i < panelContentComponent.get_text().size(); i++) {
      tbge::tui::SetBgColor(panelComponent.get_color());
      tbge::tui::SetFgColor(panelComponent.get_border_color());
      tbge::tui::SetCursorPosition(panelComponent.get_position() +
                                   panelContentComponent.get_padding() +
                                   tbge::tui::vec2i(1, 1 + i));
      std::cout << panelContentComponent.get_text().at(i);
      tbge::tui::SetBgColor(tbge::tui::Color::kDefault);
      tbge::tui::SetFgColor(tbge::tui::Color::kDefault);
    }
  }

 private:
  unsigned int GetMaxLineWidth_(panel::Content& content) {
    unsigned int line_width = 0;
    for (auto&& line : content.get_text()) {
      if (line.length() > line_width) {
        line_width = line.length();
      }
    }
    return line_width;
  }
};
}  // namespace panel

#endif  // SRC_PANEL_CONTENT_CONTENT_SYSTEM_H_