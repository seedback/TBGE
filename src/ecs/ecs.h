/**
 * @file ecs.h
 * @brief Main include file for the Entity Component System (ECS) module.
 *
 * @details
 * This header provides all necessary includes for the complete ECS system,
 * including:
 * - Core types and configuration (context.h)
 * - Entity, component, and system management
 * - The main Coordinator interface
 * - Utility functions for console setup
 *
 * Include this single header to access the entire ECS API.
 *
 * @see coordinator.h for the main ECS interface
 * @see context.h for type definitions and configuration
 */

#ifndef TBGE_ECS_ECS_H_
#define TBGE_ECS_ECS_H_

#include "src/ecs/component/component.h"
#include "src/ecs/component_array/component_array.h"
#include "src/ecs/component_manager/component_manager.h"
#include "src/ecs/context/context.h"
#include "src/ecs/coordinator/coordinator.h"
#include "src/ecs/entity_manager/entity_manager.h"
#include "src/ecs/system/system.h"
#include "src/ecs/system_manager/system_manager.h"
#include "src/ecs/utils/setup_console.h"

#endif  // TBGE_ECS_ECS_H_