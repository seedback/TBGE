#ifndef SRC_TUI_TUI_H_
#define SRC_TUI_TUI_H_

/// @file tui.h
/// @brief Terminal User Interface / Text User Interface library.
///
/// Aggregates all TUI utilities for terminal/console control. This module provides
/// a comprehensive interface for manipulating terminal output including:
///
/// - **Text Styling**: Bold, italic, underline, strikethrough, and other attributes
/// - **Colors**: Standard, bright, and extended color support for foreground and background
/// - **Cursor Control**: Position, visibility, and movement operations
/// - **Screen Operations**: Clear, scroll, and other display operations
/// - **Character Support**: UTF-8 and Unicode character handling with ANSI compatibility
///
/// All functionality is built on ANSI escape sequences for cross-platform terminal control.
///
/// @see tbge::tui::SgrParam for available text attributes and colors
/// @see tbge::tui namespace for all functions and utilities

#include "src/tui/tui_constants.h"
#include "src/tui/tui_functions.h"
#include "src/tui/box_drawing/box_drawing_constants.h"
#include "src/tui/box_drawing/box_drawing_functions.h"

#endif // SRC_TUI_TUI_H_