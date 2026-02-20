#ifndef SRC_TERMINAL_BOX_DRAWING_BOX_DRAWING_FUNCTIONS_H_
#define SRC_TERMINAL_BOX_DRAWING_BOX_DRAWING_FUNCTIONS_H_

#include <string>
#include <variant>

#include "src/terminal/box_drawing/box_drawing_constants.h"

namespace tbge {
namespace terminal {
inline std::u32string box_drawing(Line line) {
  return std::u32string(1, char32_t(0x2500 + line));
}
inline std::u32string box_drawing(Box box) {
  return std::u32string(1, char32_t(0x2580 + box));
}
}  // namespace terminal
}  // namespace tbge

#endif  // SRC_TERMINAL_BOX_DRAWING_BOX_DRAWING_FUNCTIONS_H_
