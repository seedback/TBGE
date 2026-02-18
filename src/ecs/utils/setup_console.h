#ifndef TBGE_SRC_ECS_UTILS_SETUP_CONSOLE_H_
#define TBGE_SRC_ECS_UTILS_SETUP_CONSOLE_H_

#include "src/ecs/context/context.h"

#ifdef _WIN32
#include <windows.h>
#endif

namespace ECS::Utils {

/**
 * @brief Sets up console for UTF-8 output on Windows, or sets locale on Unix.
 * @return A dummy Entity{0} value.
 */
inline ::ECS::Entity SetupConsoleForUnicode() {
#ifdef _WIN32
  SetConsoleCP(CP_UTF8);
  SetConsoleOutputCP(CP_UTF8);
#else
  std::locale::global(std::locale(""));
  std::wcout.imbue(std::locale());
#endif
  return Entity{0};
}

}  // namespace ECS::Utils

#endif  // TBGE_SRC_ECS_UTILS_SETUP_CONSOLE_H_
