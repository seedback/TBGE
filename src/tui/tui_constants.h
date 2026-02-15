#ifndef TBGE_SRC_TUI_TUI_CONSTANTS_H_
#define TBGE_SRC_TUI_TUI_CONSTANTS_H_

#include <iostream>

/// @namespace tbge::tui
/// @brief Terminal User Interface / Text User Interface utilities.
///
/// Provides low-level abstractions for terminal/console manipulation including
/// cursor positioning, text styling (colors, bold, underline), screen clearing,
/// and other console output operations. Built on ANSI escape sequences to
/// enable cross-platform terminal control.
namespace tbge {
namespace tui {
/**
 * @enum SgrParam
 * @brief Enumerates Select Graphic Rendition (SGR) parameters for ANSI escape
 * codes.
 *
 * This enum provides symbolic names for various SGR parameters used to control
 * text formatting, color, and other attributes in terminal emulators supporting
 * ANSI escape codes.
 *
 * The values correspond to standard SGR codes, including text styles (bold,
 * italic, underline, etc.), foreground and background colors (standard and
 * bright), and various reset and special formatting options.
 *
 * - Some entries have an alias, in this case both values are equivalent.
 * - Some entries are "Rarely Supported" (Prefixed with an underscore) and use
 * is discouraged.
 * - Some entries are for internal used (Suffixed with an underscore)
 * and requires additional parameters to function.
 *
 * Example usage:
 *   - kBold: Enables bold text.
 *   - kFgRed: Sets foreground color to red.
 *   - kBgBrightBlue: Sets background color to bright blue.
 *   - kReset: Resets all attributes.
 *
 * For more details, see:
 *   -
 * https://en.wikipedia.org/wiki/ANSI_escape_code#Select_Graphic_Rendition_parameters
 */
enum SgrParam {
  kReset = 0,                  // Reset all attributes
  kBold = 1,                   // Bold text
  kFaint = 2,                  // Faint/dim text
  kItalic = 3,                 // Italic text
  kUnderline = 4,              // Underlined text
  kSlowBlink = 5,              // Slow blink
  _kFastBlink = 6,             // Fast blink (rarely supported)
  kInvert = 7,                 // Inverted/reversed colors
  kHide = 8,                   // Concealed/hidden text
  kStrikethrough = 9,          // Strikethrough text
  kFontPrimary = 10,           // Primary font
  _kFontAlt1 = 11,             // Alternate font 1 (rarely supported)
  _kFontAlt2 = 12,             // Alternate font 2 (rarely supported)
  _kFontAlt3 = 13,             // Alternate font 3 (rarely supported)
  _kFontAlt4 = 14,             // Alternate font 4 (rarely supported)
  _kFontAlt5 = 15,             // Alternate font 5 (rarely supported)
  _kFontAlt6 = 16,             // Alternate font 6 (rarely supported)
  _kFontAlt7 = 17,             // Alternate font 7 (rarely supported)
  _kFontAlt8 = 18,             // Alternate font 8 (rarely supported)
  _kFontAlt9 = 19,             // Alternate font 9 (rarely supported)
  _kFontGothic = 20,           // Gothic font (rarely supported)
  kUnderlineDouble = 21,       // Double underline
  kResetIntensity = 22,        // Reset bold/faint
  kResetItalic = 23,           // Reset italic
  kResetUnderline = 24,        // Reset underline
  kResetBlink = 25,            // Reset blink
  _kProportionalSpacing = 26,  // Proportional spacing (rarely supported)
  kResetReversed = 27,         // Reset reversed colors
  kReveal = 28,                // Reveal concealed text
  kResetStrikethrough = 29,    // Reset strikethrough
  kFgBlack = 30,               // Foreground black
  kFgRed = 31,                 // Foreground red
  kFgGreen = 32,               // Foreground green
  kFgYellow = 33,              // Foreground yellow
  kFgBlue = 34,                // Foreground blue
  kFgMagenta = 35,             // Foreground magenta
  kFgCyan = 36,                // Foreground cyan
  kFgWhite = 37,               // Foreground white
  kFgSet_ = 38,     // Set foreground color (requires additional params)
  kFgDefault = 39,  // Default foreground color
  kBgBlack = 40,    // Background black
  kBgRed = 41,      // Background red
  kBgGreen = 42,    // Background green
  kBgYellow = 43,   // Background yellow
  kBgBlue = 44,     // Background blue
  kBgMagenta = 45,  // Background magenta
  kBgCyan = 46,     // Background cyan
  kBgWhite = 47,    // Background white
  kBgSet_ = 48,     // Set background color (requires additional params)
  kBgDefault = 49,  // Default background color
  _kResetProportionalSpacing =
      50,                     // Reset proportional spacing (rarely supported)
  _kFrame = 51,               // Framed text (rarely supported)
  _kEncircle = 52,            // Encircled text (rarely supported)
  kOverline = 53,             // Overlined text
  _kResetFrame = 54,          // Reset framed/encircled (rarely supported)
  kResetOverline = 55,        // Reset overline
  _kUnderlineColorSet_ = 58,  // Set underline color (rarely supported)
  _kUnderlineColorDefault = 59,  // Default underline color (rarely supported)
  _kIdeogramUnderline = 60,      // Ideogram underline (rarely supported)
  _kIdeogramUnderlineDouble =
      61,                   // Ideogram double underline (rarely supported)
  _kIdeogramOverline = 62,  // Ideogram overline (rarely supported)
  _kIdeogramOverlineDouble = 63,  // Ideogram double overline (rarely supported)
  _kIdeogramStressMarking = 64,   // Ideogram stress marking (rarely supported)
  _kResetIdeogram = 65,           // Reset ideogram (rarely supported)
  _kSuperscript = 73,             // Superscript (rarely supported)
  _kSubscript = 74,               // Subscript (rarely supported)
  _kResetSuperscript = 75,  // Reset superscript/subscript (rarely supported)
  kFgBrightBlack = 90,      // Foreground bright black
  kFgBrightRed = 91,        // Foreground bright red
  kFgBrightGreen = 92,      // Foreground bright green
  kFgBrightYellow = 93,     // Foreground bright yellow
  kFgBrightBlue = 94,       // Foreground bright blue
  kFgBrightMagenta = 95,    // Foreground bright magenta
  kFgBrightCyan = 96,       // Foreground bright cyan
  kFgBrightWhite = 97,      // Foreground bright white
  kBgBrightBlack = 100,     // Background bright black
  kBgBrightRed = 101,       // Background bright red
  kBgBrightGreen = 102,     // Background bright green
  kBgBrightYellow = 103,    // Background bright yellow
  kBgBrightBlue = 104,      // Background bright blue
  kBgBrightMagenta = 105,   // Background bright magenta
  kBgBrightCyan = 106,      // Background bright cyan
  kBgBrightWhite = 107,     // Background bright white

  // Aliases
  kResetBold = kResetItalic,                  // Alias for reset bold
  _kResetEncircle = _kResetFrame,             // Alias for reset encircle
  _kIdeogramRightLine = _kIdeogramUnderline,  // Alias
  _kIdeogramRightLineDouble = _kIdeogramUnderlineDouble,  // Alias
  _kIdeogramLeftLine = _kIdeogramOverline,                // Alias
  _kIdeogramLeftLineDouble = _kIdeogramOverlineDouble,    // Alias
  _kResetSubcript = _kResetSuperscript,  // Alias for reset subscript
};

/**
 * @brief Enumeration of standard and bright terminal foreground colors.
 *
 * Maps to SGR (Select Graphic Rendition) parameters for setting foreground
 * text colors in terminal output. Includes standard 8 colors, their bright
 * variants, and a default color value.
 */
enum Color {
  // Foreground colors
  kBlack = SgrParam::kFgBlack,
  kRed = SgrParam::kFgRed,
  kGreen = SgrParam::kFgGreen,
  kYellow = SgrParam::kFgYellow,
  kBlue = SgrParam::kFgBlue,
  kMagenta = SgrParam::kFgMagenta,
  kCyan = SgrParam::kFgCyan,
  kWhite = SgrParam::kFgWhite,
  kBrightBlack = SgrParam::kFgBrightBlack,
  kBrightRed = SgrParam::kFgBrightRed,
  kBrightGreen = SgrParam::kFgBrightGreen,
  kBrightYellow = SgrParam::kFgBrightYellow,
  kBrightBlue = SgrParam::kFgBrightBlue,
  kBrightMagenta = SgrParam::kFgBrightMagenta,
  kBrightCyan = SgrParam::kFgBrightCyan,
  kBrightWhite = SgrParam::kFgBrightWhite,
  kDefault = SgrParam::kFgDefault,
};

/**
 * @brief Offset to convert a foreground color SGR parameter to background.
 *
 * In ANSI color codes, background colors are derived by adding 10 to the
 * corresponding foreground color value. For example, kFgRed (31) + 10 = kBgRed
 * (41).
 */
const int kBackgroundColorOffset = 10;

// Unicode box-drawing character constants
const std::u8string kLineUpDown = u8"\u2502";           // │ vertical line
const std::u8string kLineLeftRight = u8"\u2500";        // ─ horizontal line
const std::u8string kLineUpLeft = u8"\u2518";           // ┘ up-left corner
const std::u8string kLineUpRight = u8"\u2514";          // └ up-right corner
const std::u8string kLineDownLeft = u8"\u2510";         // ┐ down-left corner
const std::u8string kLineDownRight = u8"\u250C";        // ┌ down-right corner
const std::u8string kLineUpDownLeft = u8"\u2524";       // ┤ vertical-left junction
const std::u8string kLineUpDownRight = u8"\u251C";      // ├ vertical-right junction
const std::u8string kLineUpLeftRight = u8"\u2534";      // ┴ up and left-right junction
const std::u8string kLineDownLeftRight = u8"\u252C";    // ┬ down and left-right junction
const std::u8string kLineUpDownLeftRight = u8"\u253C";  // ┼ four-way junction
const std::u8string kLineDDUpDown = u8"\u2551";         // ║ double vertical line
const std::u8string kLineDDLeftRight = u8"\u2550";      // ═ double horizontal line
const std::u8string kLineDDUpLeft = u8"\u255B";         // ╝ double up-left corner
const std::u8string kLineDDUpRight = u8"\u2559";        // ╚ double up-right corner
const std::u8string kLineDDDownLeft = u8"\u2557";       // ╗ double down-left corner
const std::u8string kLineDDDownRight = u8"\u2554";      // ╔ double down-right corner
const std::u8string kLineDDUpDownLeft = u8"\u2563";     // ╣ double vertical-left junct
const std::u8string kLineDDUpDownRight = u8"\u2560";    // ╠ double vertical-right junc
const std::u8string kLineDDUpLeftRight = u8"\u2567";    // ╩ double up and horizontal junction
const std::u8string kLineDDDownLeftRight = u8"\u2566";  // ╦ double down and horizontal junction
const std::u8string kLineDDUpDownLeftRight = u8"\u256C"; // ╬ double all four junction

struct vec2i {
  vec2i() : vec2i(0, 0) {}
  vec2i(int x, int y) {
    this->x = x;
    this->y = y;
  }
  int x;
  int y;

  vec2i operator+(const vec2i& other) const {
    return vec2i(x + other.x, y + other.y);
  }

  vec2i operator-(const vec2i& other) const {
    return vec2i(x - other.x, y - other.y);
  }

  vec2i operator*(const vec2i& other) const {
    return vec2i(x * other.x, y * other.y);
  }

  vec2i operator/(const vec2i& other) const {
    return vec2i(x / other.x, y / other.y);
  }
};

const std::u8string endl = u8"\n";  // newline

// ### ANSI Control Codes ###
// C0   (https://en.wikipedia.org/wiki/C0_and_C1_control_codes#C0_controls)
const std::u8string kAnsiNul = u8"\x00";  // Null
const std::u8string kAnsiBel = u8"\x07";  // Bell
const std::u8string kAnsiBs = u8"\x08";   // Backspace
const std::u8string kAnsiHt = u8"\x09";   // Horizontal Tab
const std::u8string kAnsiLf = u8"\x0A";   // Line Feed
const std::u8string kAnsiVt = u8"\x0B";   // Vertical Tab
const std::u8string kAnsiFf = u8"\x0C";   // Form Feed
const std::u8string kAnsiCr = u8"\x0D";   // Carriage Return
const std::u8string kAnsiEsc = u8"\x1B";  // Escape

// C1   (https://en.wikipedia.org/wiki/C0_and_C1_control_codes#C1_controls)
// Break Permitted Here
const std::u8string kAnsiBph = u8"\x82";
// No Break Here
const std::u8string kAnsiNbh = u8"\x83";
// Index eg. Cross-Platform LF
const std::u8string kAnsiInd = u8"\x84";
// Next Line eg. Cross-Platform CR-LF
const std::u8string kAnsiNel = u8"\x85";
// Set tab-stop
const std::u8string kAnsiHts = u8"\x88";
// Right-justify the text since the last tab against the next tab stop.
const std::u8string kAnsiHtj = u8"\x89";
// Set vertical tab-stop
const std::u8string kAnsiVts = u8"\x8A";
// Reverse line-feed
const std::u8string kAnsiRi = u8"\x8D";
// Cancel character eg. destructive backspace
const std::u8string kAnsiCch = u8"\x94";

// Shifts next character to G2 character set
const std::u8string kAnsiSS2 = kAnsiEsc + u8"N";
// Shifts next character to G3 character set
const std::u8string kAnsiSS3 = kAnsiEsc + u8"O";
// Device Control String
const std::u8string kAnsiDCS = kAnsiEsc + u8"P";
// Control Sequence Introducer (ESC)
const std::u8string kAnsiCsi = kAnsiEsc + u8"[";
// String Terminator eg. "\"
const std::u8string kAnsiSt = kAnsiEsc + u8"\\";
// Operating System Command (OSC)
const std::u8string kAnsiOsc = kAnsiEsc + u8"]";

// ### CSI Commands ###
// https://en.wikipedia.org/wiki/ANSI_escape_code#Control_Sequence_Introducer_commands
const std::u8string kAnsiCuuSuffix = u8"A";
const std::u8string kAnsiCudSuffix = u8"B";
const std::u8string kAnsiCufSuffix = u8"C";
const std::u8string kAnsiCubSuffix = u8"D";
const std::u8string kAnsiCnlSuffix = u8"E";
const std::u8string kAnsiCplSuffix = u8"F";
const std::u8string kAnsiChaSuffix = u8"G";
const std::u8string kAnsiCupSuffix = u8"H";
const std::u8string kAnsiEdSuffix = u8"J";
const std::u8string kAnsiElSuffix = u8"K";
const std::u8string kAnsiSuSuffix = u8"S";
const std::u8string kAnsiSdSuffix = u8"T";
const std::u8string kAnsiHvpSuffix = u8"f";
const std::u8string kAnsiSgrSuffix = u8"m";
const std::u8string kAnsiDsr = kAnsiCsi + u8"6n";

// Save Cursor Position
const std::u8string kAnsiScp = kAnsiCsi + u8"s";
// Restore Cursor Position
const std::u8string kAnsiRcp = kAnsiCsi + u8"u";
// Save Cursor
const std::u8string kAnsiDecSc = kAnsiEsc + u8"7";
// Restore Cursor
const std::u8string kAnsiDecRc = kAnsiEsc + u8"8";
// Set line to Double-Height Characters top half
const std::u8string kAnsiDecDht = kAnsiEsc + u8"#3";
// Set line to Double-Height Characters bottom half
const std::u8string kAnsiDecDhb = kAnsiEsc + u8"#4";
// Set line to Single-Width Characters
const std::u8string kAnsiDecSwl = kAnsiEsc + u8"#5";
// Set line to Double-Width Characters
const std::u8string kAnsiDecDwl = kAnsiEsc + u8"#6";

// ## Other
const std::u8string kAnsiClearScreen = kAnsiCsi + u8"2J" + kAnsiCsi + u8"3J";
const std::u8string kAnsiConsoleTitleStart = kAnsiOsc + u8"0;";
const std::u8string kAnsiConsoleTitleEnd = kAnsiSt;
const std::u8string kAnsiAttributeReset = kAnsiCsi + u8"0m";
const std::u8string kAnsiCursorHide = kAnsiCsi + u8"?25l";
const std::u8string kAnsiCursorShow = kAnsiCsi + u8"?25h";
const std::u8string kAnsiCursorHome = kAnsiCsi + u8"H";
}  // namespace tui
}  // namespace tbge

#endif  // TBGE_SRC_PANEL_PANEL_CONSTANTS_H_