#ifndef TBGE_SRC_TUI_TUI_FUNCTIONS_H_
#define TBGE_SRC_TUI_TUI_FUNCTIONS_H_

#include <codecvt>
#include <iostream>
#include <locale>
#include <string>

#include "src/tui/tui_constants.h"

#ifdef _WIN32
#include <windows.h>  // for WinAPI and Sleep()
#define _NO_OLDNAMES  // for MinGW compatibility
#include <conio.h>    // for getch() and kbhit()
#endif                // _WIN32

/// @namespace tbge::tui
/// @brief Terminal User Interface / Text User Interface utilities.
///
/// Provides low-level abstractions for terminal/console manipulation including
/// cursor positioning, text styling (colors, bold, underline), screen clearing,
/// and other console output operations. Built on ANSI escape sequences to
/// enable cross-platform terminal control.
namespace tbge {
namespace tui {
// Check if a character is wide (double-width in console)
inline bool is_wide_character(char32_t codepoint) {
  // Wide character ranges: Hangul, CJK, Emoji, Blocks, etc.
  return (codepoint >= 0x1100 && codepoint <= 0x115F) ||  // Hangul Jamo
         (codepoint >= 0x2E80 && codepoint <= 0xA4CF) ||  // CJK ranges
         (codepoint >= 0xAC00 && codepoint <= 0xD7AF) ||  // Hangul Syllables
         (codepoint >= 0xF900 && codepoint <= 0xFAFF) ||  // CJK Compatibility
         (codepoint >= 0x1F000 && codepoint <= 0x1FFFF);  // SMP (emoji, blocks)
}

// Prints out UTF-8 formatted strings from Unicode codepoints
// Automatically adjusts cursor for wide characters
inline void unicode_print(const std::u32string& text = U"") {
  std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
  std::cout << converter.to_bytes(text);

  // Move cursor left for each wide character to compensate for extra width
  for (char32_t codepoint : text) {
    if (is_wide_character(codepoint)) {
      std::cout << "\033[D";  // ANSI: Cursor Left
    }
  }
}

inline std::u8string int_to_u8(int i) {
  std::string s = std::to_string(i);
  return std::u8string(s.begin(), s.end());
}

inline std::u8string AnsiPositionCursor(int x, int y) {
  return kAnsiCsi + int_to_u8(y) + u8";" + int_to_u8(x) + u8"H";
}

inline std::u8string AnsiSetConsoleTitle(const std::string& title) {
  std::u8string u8title(title.begin(), title.end());
  return kAnsiConsoleTitleStart + u8title + kAnsiConsoleTitleEnd;
}

inline std::u8string AnsiCuu(int n = 1) {
  return kAnsiCsi + int_to_u8(n) + kAnsiCuuSuffix;
}
inline std::u8string AnsiCud(int n = 1) {
  return kAnsiCsi + int_to_u8(n) + kAnsiCudSuffix;
}
inline std::u8string AnsiCuf(int n = 1) {
  return kAnsiCsi + int_to_u8(n) + kAnsiCufSuffix;
}
inline std::u8string AnsiCub(int n = 1) {
  return kAnsiCsi + int_to_u8(n) + kAnsiCubSuffix;
}
inline std::u8string AnsiCup(int x, int y) {
  return kAnsiCsi + int_to_u8(y) + u8";" + int_to_u8(x) + kAnsiCupSuffix;
}

template <typename... Args>
inline std::u8string AnsiSgr(Args... args) {
  static_assert(
      (std::conjunction_v<std::disjunction<std::is_same<Args, int>,
                                           std::is_same<Args, SgrParam>>...>),
      "All arguments to AnsiSgr must be int or SgrParam");
  std::u8string result = kAnsiCsi;
  const char8_t* sep = u8"";
  ((result += sep, result += int_to_u8(static_cast<int>(args)), sep = u8";"),
   ...);
  result += kAnsiSgrSuffix;
  return result;
}

inline std::u8string AnsiClearScreen() { return kAnsiClearScreen; }

inline void ClearScreen() {
  std::cout << reinterpret_cast<const char*>(AnsiClearScreen().data());
}

inline void Cls() { ClearScreen(); }

inline std::u8string AnsiClearScreenAndReset() { return kAnsiEsc + u8"c"; }

inline void ClearScreenAndReset() {
  std::cout << reinterpret_cast<const char*>(AnsiClearScreenAndReset().data());
}

inline void Clsr() { ClearScreenAndReset(); }

inline void SetColor(int color) {
  std::cout << reinterpret_cast<const char*>(
      (kAnsiCsi + int_to_u8(color) + u8"m").data());
}

/**
 * @brief Set the Foreground color using a predefined 8-bit value
 *
 * @param color The ANSI integer representation of the color
 *
 * For more details, see:
 * - https://en.wikipedia.org/wiki/ANSI_escape_code#8-bit
 */
inline void SetFgColor8Bit(int n) {
  if (n < 0) n = 0;
  if (n > 255) n = 255;
  std::cout << reinterpret_cast<const char*>(
      (kAnsiCsi + int_to_u8(SgrParam::kFgSet_) + u8";5;" + int_to_u8(n) + u8"m")
          .data());
}

/**
 * @brief Set the Foreground color using a set of 8 bit integers, representing
 * the red, green and blue value of the color.
 *
 * @param r Red
 * @param g Green
 * @param b Blue
 *
 * For more details, see:
 * - https://en.wikipedia.org/wiki/ANSI_escape_code#24-bit
 */
inline void SetFgColorRgb(int r, int g, int b) {
  if (r < 0) r = 0;
  if (r > 255) r = 255;
  if (g < 0) g = 0;
  if (g > 255) g = 255;
  if (b < 0) b = 0;
  if (b > 255) b = 255;
  std::cout << reinterpret_cast<const char*>(
      (kAnsiCsi + int_to_u8(SgrParam::kFgSet_) + u8";2;" + int_to_u8(r) +
       u8";" + int_to_u8(g) + u8";" + int_to_u8(b) + u8"m")
          .data());
}

/**
 * @brief Set the Foreground color using the Color enum
 * @sa tui::Color
 *
 * @param color The color to set, using a predefined Color enum value
 * @return An ANSI escape sequence string that sets the foreground color
 */
inline void SetFgColor(Color color) {
  std::cout << reinterpret_cast<const char*>(
      (kAnsiCsi + int_to_u8(int(color)) + u8"m").data());
}

inline void SetFgColor(int color) {
  std::cout << reinterpret_cast<const char*>(
      (kAnsiCsi + int_to_u8(color) + u8"m").data());
}

/**
 * @brief Set the Foreground color using a predefined 8-bit value
 *
 * @param color The ANSI integer representation of the color
 *
 * For more details, see:
 * - https://en.wikipedia.org/wiki/ANSI_escape_code#8_bit
 */
inline void SetBgColor8Bit(int color) {
  if (color < 0) color = 0;
  if (color > 255) color = 255;
  std::cout << reinterpret_cast<const char*>(
      (kAnsiCsi + int_to_u8(SgrParam::kBgSet_) + u8";5;" + int_to_u8(color) +
       u8"m")
          .data());
}

inline void SetBgColorRgb(int r, int g, int b) {
  if (r < 0) r = 0;
  if (r > 255) r = 255;
  if (g < 0) g = 0;
  if (g > 255) g = 255;
  if (b < 0) b = 0;
  if (b > 255) b = 255;
  std::cout << reinterpret_cast<const char*>(
      (kAnsiCsi + int_to_u8(SgrParam::kBgSet_) + u8";2;" + int_to_u8(r) +
       u8";" + int_to_u8(g) + u8";" + int_to_u8(b) + u8"m")
          .data());
}

inline void SetBgColor(Color color) {
  std::cout << reinterpret_cast<const char*>(
      (kAnsiCsi + int_to_u8(int(color) + kBackgroundColorOffset) + u8"m")
          .data());
}

inline void SetBgColor(int color) {
  std::cout << reinterpret_cast<const char*>(
      (kAnsiCsi + int_to_u8(color + kBackgroundColorOffset) + u8"m").data());
}

/**
 * @brief Sets the cursor position in the terminal
 *
 * Moves the cursor to the specified (x, y) coordinates.
 *
 * @param x The horizontal position (column)
 * @param y The vertical position (row)
 */
inline void SetCursorPosition(long x, long y) {
  auto cmd = AnsiCup(static_cast<int>(x), static_cast<int>(y));
  std::cout << reinterpret_cast<const char*>(cmd.data());
}

/**
 * @brief Sets the cursor position using a 2D vector
 *
 * @param pos A 2D vector containing x (column) and y (row) coordinates
 */
inline void SetCursorPosition(vec2i pos) { SetCursorPosition(pos.x, pos.y); }

inline vec2i GetCursorPosition() {
  vec2i pos = {-1, -1};

#ifdef _WIN32
  // Send DSR (Device Status Report) request
  std::cout << reinterpret_cast<const char*>(u8"\033[6n") << std::flush;

  // Read the response: ESC[{row};{col}R
  std::u8string response;
  char ch;

  // Read until we get the 'R' at the end
  while ((ch = _getch()) != 'R') {
    response += static_cast<char8_t>(ch);
  }
  response += u8'R';

  // Parse the response: should be like "\033[24;80R"
  if (response.length() > 3 && response[0] == u8'\033' &&
      response[1] == u8'[') {
    std::u8string coords =
        response.substr(2, response.length() - 3);  // Remove ESC[ and R
    size_t semicolon = coords.find(u8';');
    if (semicolon != std::u8string::npos) {
      pos.y = std::stoi(std::string(coords.substr(0, semicolon).begin(),
                                    coords.substr(0, semicolon).end()));
      pos.x = std::stoi(std::string(coords.substr(semicolon + 1).begin(),
                                    coords.substr(semicolon + 1).end()));
    }
  }

#else
  // Linux/macOS implementation
  struct termios old_termios, new_termios;

  // Save current terminal settings
  tcgetattr(STDIN_FILENO, &old_termios);
  new_termios = old_termios;

  // Set terminal to raw mode
  new_termios.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

  // Send DSR request
  std::cout << "\033[6n" << std::flush;

  // Read response
  std::string response;
  char ch;
  while (read(STDIN_FILENO, &ch, 1) == 1 && ch != 'R') {
    response += ch;
  }
  response += 'R';

  // Restore terminal settings
  tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);

  // Parse response
  if (response.length() > 3 && response[0] == '\033' && response[1] == '[') {
    std::string coords = response.substr(2, response.length() - 3);
    size_t semicolon = coords.find(';');
    if (semicolon != std::string::npos) {
      pos.row = std::stoi(coords.substr(0, semicolon));
      pos.col = std::stoi(coords.substr(semicolon + 1));
    }
  }
#endif

  return pos;
}

inline vec2i GetConsoleSize() {
  vec2i position = GetCursorPosition();
  AnsiCup(999, 999);
  vec2i size = GetCursorPosition();
  AnsiCup(position.x, position.y);
  return size;
}

// void SetConsoleTitle(ws) {

// }

}  // namespace tui
}  // namespace tbge

#endif  // TBGE_SRC_PANEL_PANEL_FUNCTIONS_H_