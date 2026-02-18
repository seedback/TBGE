#ifndef TBGE_SRC_ECS_CONFIG_H_
#define TBGE_SRC_ECS_CONFIG_H_

#include <bitset>
#include <cstdint>
#include <limits>

#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#include <windows.h>
#ifdef max
#undef max
#endif  // max
#ifdef min
#undef min
#endif  // min
#endif  // _WIN32

namespace ECS {

// ============================================================================
// TYPE CONFIGURATION
// ============================================================================
// Use ECS_CONFIG_64BIT to switch to 64-bit entities and 32-bit component IDs.
// Default (without the define): 32-bit entities and 16-bit component IDs.
//
// In your project's config/main header, define ECS_CONFIG_64BIT before
// including any ECS headers if you want the larger type configuration.

#ifdef ECS_CONFIG_64BIT
using Entity = std::uint64_t;
using ComponentTypeId = std::uint32_t;
constexpr size_t kMaxComponentTypes = std::numeric_limits<ComponentTypeId>::max();
#else
using Entity = std::uint32_t;
using ComponentTypeId = std::uint16_t;
constexpr size_t kMaxComponentTypes = std::numeric_limits<ComponentTypeId>::max();
#endif

using Signature = std::bitset<kMaxComponentTypes>;

}  // namespace ECS

#endif // TBGE_SRC_ECS_CONFIG_H_