#ifndef TBGE_SRC_WINDOWS_PANEL_H_
#define TBGE_SRC_WINDOWS_PANEL_H_

#include <iostream>
#include <utility>

#include "src/ecs/ecs.h"
#include "src/tui/tui.h"

namespace panel {

template <typename Context = ECS::Context<>>
class Panel {
 public:
  Panel(tbge::tui::vec2i position, tbge::tui::vec2i size, int z,
        tbge::tui::Color color = tbge::tui::Color::kDefault,
        tbge::tui::Color border_color = tbge::tui::Color::kDefault) {
    position_ = position;
    size_ = size;
    z_ = z;
    color_ = color;
    border_color_ = border_color;
  }

  void Draw() { 
    DrawRectangle(position_, size_, color_, border_color_); }

  void set_z(int z) {
    z_ = z;
  }

  int get_z() {
    return z_;
  }

 private:
  tbge::tui::vec2i position_;
  tbge::tui::vec2i size_;
  tbge::tui::Color color_;
  tbge::tui::Color border_color_;
  int z_;

  static void DrawRectangle(
      tbge::tui::vec2i position, tbge::tui::vec2i size, tbge::tui::Color color,
      tbge::tui::Color borderColor = tbge::tui::Color::kDefault) {
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
};
}  // namespace panel
#endif  // TBGE_SRC_WINDOWS_PANEL_H_