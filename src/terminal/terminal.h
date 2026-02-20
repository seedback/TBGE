#ifndef SRC_TERMINAL_TERMINAL_H_
#define SRC_TERMINAL_TERMINAL_H_

/// @file terminal.h
/// @brief Terminal User Interface / Text User Interface library.
///
/// Aggregates all Terminal utilities for terminal/console control. This module provides
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
/// @see tbge::terminal::SgrParam for available text attributes and colors
/// @see tbge::terminal namespace for all functions and utilities

#include "src/terminal/terminal_constants.h"
#include "src/terminal/terminal_functions.h"
#include "src/terminal/box_drawing/box_drawing_constants.h"
#include "src/terminal/box_drawing/box_drawing_functions.h"

#endif // SRC_TERMINAL_TERMINAL_H_
