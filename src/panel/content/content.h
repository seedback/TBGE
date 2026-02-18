#ifndef TBGE_SRC_PANEL_CONTENT_CONTENT_H_
#define TBGE_SRC_PANEL_CONTENT_CONTENT_H_

#include <string>
#include <vector>

#include "src/tui/tui.h"

namespace panel {
class Content {
 public:
  Content() : Content(std::vector<std::string>(0), {0, 0}) {}

  Content(std::vector<std::string> text, tbge::tui::vec2i padding) {
    text_ = text;
    padding_ = padding;
  }

  Content(std::vector<std::string> text) : Content(text, {0, 0}) {}

  Content(std::string line, tbge::tui::vec2i padding)
      : Content(std::vector<std::string>{line}, padding) {}

  Content(std::string line) : Content(line, {0, 0}) {}

  void set_text(std::vector<std::string> text) { text_ = text; }
  std::vector<std::string> get_text() { return text_; }
  void set_line(unsigned int index, std::string line) {
    if (index >= text_.size()) {
      text_.resize(index + 1);
    }
    text_.at(index) = line;
  }
  std::string get_line(unsigned int index) { return text_.at(index); }
  void set_padding(tbge::tui::vec2i padding) { padding_ = padding; }
  void set_padding(int x, int y) { padding_ = {x, y}; }
  tbge::tui::vec2i get_padding() { return padding_; }

 private:
  std::vector<std::string> text_;
  tbge::tui::vec2i padding_;
};

}  // namespace panel

#endif  // TBGE_SRC_PANEL_CONTENT_CONTENT_H_