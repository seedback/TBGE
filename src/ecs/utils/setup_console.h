/**
 * @file setup_console.h
 * @brief Utility function for configuring console character encoding.
 *
 * @details
 * Provides platform-specific setup for UTF-8 console output on Windows and
 * locale configuration on Unix systems.
 */

#ifndef TBGE_ECS_UTILS_SETUP_CONSOLE_H_
#define TBGE_ECS_UTILS_SETUP_CONSOLE_H_

#include <iostream>
#include <locale>

#include "src/ecs/context/context.h"

#ifdef _WIN32
#include <windows.h>
#endif

namespace tbge::ecs::utils {

/**
 * @brief Sets up console for UTF-8 output on Windows, or configures the global
 * locale on Unix systems.
 *
 * @details
 * On Windows, sets both the console input and output code pages to UTF-8.
 * On other systems, sets the global locale to the user's locale and configures
 * wide character output accordingly.
 */
inline void SetupConsoleForUnicode() noexcept {
#ifdef _WIN32
  SetConsoleCP(CP_UTF8);
  SetConsoleOutputCP(CP_UTF8);
#else
  std::locale::global(std::locale(""));
  std::wcout.imbue(std::locale());
#endif
}

}  // namespace ECS::utils

#endif  // TBGE_ECS_UTILS_SETUP_CONSOLE_H_
