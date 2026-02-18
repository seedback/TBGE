#include "src/panel/panel.h"
#include "src/panel/content/panel_content_system.h"

extern ECS::Coordinator gCoordinator;

namespace panel {

Panel::Panel(tbge::tui::vec2i position, tbge::tui::vec2i size,
             int initial_z, tbge::tui::Color color,
             tbge::tui::Color border_color) {
  position_ = position;
  size_ = size;
  z_index_ = initial_z;
  color_ = color;
  border_color_ = border_color;
}

void Panel::Draw() {
  DrawRectangle(position_, size_, color_, border_color_);

  gCoordinator.GetSystem<PanelContentSystem>()->RedrawEntityContent(
      this->get_entity_id());
}

void Panel::set_z_index(int z) {
  z_index_ = z;
}

int Panel::get_z_index() {
  return z_index_;
}

void Panel::DrawRectangle(tbge::tui::vec2i position,
                          tbge::tui::vec2i size,
                          tbge::tui::Color color,
                          tbge::tui::Color borderColor) {
  tbge::tui::SetBgColor(color);
  tbge::tui::SetFgColor(borderColor);

  for (int x = 0; x < size.x; x++) {
    for (int y = 0; y < size.y; y++) {
      tbge::tui::SetCursorPosition(position + tbge::tui::vec2i(x, y));
      if (x == 0 && y == 0) {
        tbge::tui::unicode_print(
            tbge::tui::box_drawing(tbge::tui::Line::kDDDownRight));
        continue;
      }
      if (x == size.x - 1 && y == 0) {
        tbge::tui::unicode_print(
            tbge::tui::box_drawing(tbge::tui::Line::kDDDownLeft));
        continue;
      }
      if (x == 0 && y == size.y - 1) {
        tbge::tui::unicode_print(
            tbge::tui::box_drawing(tbge::tui::Line::kDDUpRight));
        continue;
      }
      if (x == size.x - 1 && y == size.y - 1) {
        tbge::tui::unicode_print(
            tbge::tui::box_drawing(tbge::tui::Line::kDDUpLeft));
        continue;
      }
      if (x != 0 && x != size.x - 1) {
        if (y == 0 || y == size.y - 1) {
          tbge::tui::unicode_print(
              tbge::tui::box_drawing(tbge::tui::Line::kDDLeftRight));
          continue;
        }
      }
      if (x == 0 || x == size.x - 1) {
        if (y != 0 && y != size.y - 1) {
          tbge::tui::unicode_print(
              tbge::tui::box_drawing(tbge::tui::Line::kDDUpDown));
          continue;
        }
      }
      tbge::tui::unicode_print(U" ");
    }
  }

  tbge::tui::SetBgColor(tbge::tui::Color::kDefault);
  tbge::tui::SetFgColor(tbge::tui::Color::kDefault);
}

}  // namespace panel
