/**
 * @file tbge.h
 * @brief Main include file for TBGE (Text-Based Game Engine).
 *
 * @details
 * This is the primary entry point for using TBGE in external projects. Include
 * this single header to access all TBGE functionality including:
 *
 * - **ECS System**: Complete Entity Component System for game logic
 * - **Terminal**: Text-based user interface and terminal control utilities
 * - **Future Extensions**: Additional modules and features can be added here
 *
 * Example usage:
 * @code
 *   #include "tbge.h"
 *
 *   // Access ECS components
 *   auto coordinator = ecs::Coordinator::GetInstance();
 *
 *   // Access Terminal utilities
 *   tbge::terminal::SetForegroundColor(tbge::terminal::kColorGreen);
 * @endcode
 *
 * @see tbge/ecs/ecs.h for Entity Component System documentation
 * @see tbge/terminal/terminal.h for Terminal utilities documentation
 */

#ifndef TBGE_TBGE_H_
#define TBGE_TBGE_H_

// Core ECS module
#include "src/ecs/ecs.h"

// Terminal
#include "src/terminal/terminal.h"

// Future extensions can be added here:
// #include "src/audio/audio.h"
// #include "src/graphics/graphics.h"
// #include "src/physics/physics.h"

namespace tbge {
ecs::Coordinator g_coordinator;
}

#endif  // TBGE_TBGE_H_
