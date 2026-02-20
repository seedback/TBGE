#ifndef TBGE_WINDOWS_PANEL_H_
#define TBGE_WINDOWS_PANEL_H_

#include <iostream>
#include <utility>

#include "src/ecs/ecs.h"
#include "src/tui/tui.h"

namespace panel {

class Panel : public ECS::Component {
 public:
  Panel(tbge::tui::vec2i position, tbge::tui::vec2i size, int initial_z,
        tbge::tui::Color color = tbge::tui::Color::kDefault,
        tbge::tui::Color border_color = tbge::tui::Color::kDefault);

  void Draw();

  void set_position(tbge::tui::vec2i position) { position_ = position; }
  void set_position(int x, int y) { position_ = {x, y}; }
  tbge::tui::vec2i get_position() { return position_; }

  void set_size(tbge::tui::vec2i size) { size_ = size; }
  void set_size(int x, int y) { size_ = {x, y}; }
  tbge::tui::vec2i get_size() { return size_; }

  void set_color(tbge::tui::Color color) { color_ = color; }
  tbge::tui::Color get_color() { return color_; }

  void set_border_color(tbge::tui::Color border_color) {
    border_color_ = border_color;
  }
  tbge::tui::Color get_border_color() { return border_color_; }

  void set_z_index(int z);
  int get_z_index();

 private:
  tbge::tui::vec2i position_;
  tbge::tui::vec2i size_;
  tbge::tui::Color color_;
  tbge::tui::Color border_color_;
  int z_index_;

  static void DrawRectangle(
      tbge::tui::vec2i position, tbge::tui::vec2i size, tbge::tui::Color color,
      tbge::tui::Color borderColor = tbge::tui::Color::kDefault);
};
}  // namespace panel

#endif  // TBGE_WINDOWS_PANEL_H_