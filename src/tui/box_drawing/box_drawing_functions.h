#ifndef SRC_TUI_BOX_DRAWING_BOX_DRAWING_FUNCTIONS_H_
#define SRC_TUI_BOX_DRAWING_BOX_DRAWING_FUNCTIONS_H_

#include <string>
#include <variant>

#include "src/tui/box_drawing/box_drawing_constants.h"

namespace tbge {
namespace tui {
std::u32string box_drawing(Line line) {
  return std::u32string(1, char32_t(0x2500 + line));
}
std::u32string box_drawing(Box box) {
  return std::u32string(1, char32_t(0x2580 + box));
}
}  // namespace tui
}  // namespace tbge

#endif  // SRC_TUI_BOX_DRAWING_BOX_DRAWING_FUNCTIONS_H_