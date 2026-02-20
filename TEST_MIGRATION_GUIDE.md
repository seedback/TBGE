# ECS Test Migration Guide: Macro-Based Configuration

## Overview
The ECS system has migrated from a **template-based Context** system to a **macro-based configuration** system. All test files must be updated to work with the new API.

---

## Changes Summary

### OLD API (Template-Based)
```cpp
template<typename Config> class ECS::Context<Config>
ECS::kMaxEntities          // Varied by Config
ECS::kMaxComponentTypes    // Varied by Config
TestContext::Entity        // From template specialization
```

### NEW API (Macro-Based)
```cpp
// Configuration macros (set before including ECS headers):
#define ECS_ENTITY_CONFIG 32              // Entity type bit width: 8, 16, 32, or 64
#define ECS_COMPONENT_CONFIG 16           // ComponentTypeId bit width: 8, 16, or 32
#define ECS_MAX_COMPONENT_TYPES 1024      // Maximum component types

// Direct types in ECS namespace:
ECS::Entity                           // Direct type (no template)
ECS::ComponentTypeId                  // Direct type (no template)
ECS::Signature                        // Direct bitset
ECS::kMaxComponentTypes              // Constant from context.h
std::numeric_limits<ECS::Entity>::max() // Max entities (not templated)
```

---

## File-by-File Changes

### 1. **context_test.cc** - COMPLETE REWRITE
**Status:** ❌ Broken (uses old template-based API that no longer exists)

**What was wrong:**
- Tests instantiated `ECS::Context<>` with template parameters (no longer exists)
- Tests checked `TestContext::Entity`, `TestContext::ComponentTypeId`, etc. (these are now direct types)
- Tests expected mutable `kMaxEntities` and `kMaxComponentTypes` (now compile-time constants)

**What to do:**
- Remove all template specializations
- Test the macro-based configuration directly
- Test that the types are set up correctly based on the macro values
- Verify `ECS::kMaxComponentTypes` equals the macro value
- Verify Entity size based on `ECS_ENTITY_CONFIG`

**Example changes:**
```cpp
// OLD:
using TestContext = ECS::Context<>;
EXPECT_EQ(TestContext::kMaxEntities, 65535);

// NEW:
EXPECT_EQ(ECS::kMaxComponentTypes, ECS_MAX_COMPONENT_TYPES);
EXPECT_EQ(sizeof(ECS::Entity), sizeof(std::uint32_t));
```

---

### 2. **entity_manager_test.cc** - MINOR FIX
**Status:** ⚠️ Needs fix (references `ECS::kMaxEntities` which doesn't exist in new form)

**What needs fixing:**
- Line with comment `// 10 is the max entities configured in the test` - needs to use proper max
- Need to replace `ECS::kMaxEntities` references with `std::numeric_limits<ECS::Entity>::max()`

**Changes:**
```cpp
// OLD:
invalid_entity = 10;  // Beyond default max of 10 allowed in test
test_entity_manager.CreateEntity(); // 10 times
EXPECT_DEATH(..., "...maximum amount of Entities is.*...");

// NEW:
invalid_entity = std::numeric_limits<ECS::Entity>::max();
// Create many entities until limit (but keep test reasonable)
// Or just test with valid entities and skip the overflow test if Entity max is too large
```

---

### 3. **component_manager_test.cc** - NO CHANGES NEEDED
**Status:** ✅ Works as-is

The test doesn't use:
- Template-based Context
- kMaxEntities or kMaxComponentTypes
- TestContext type references

---

### 4. **coordinator_test.cc** - NO CHANGES NEEDED
**Status:** ✅ Works as-is

The test uses public API and doesn't reference old template system.

---

### 5. **component_array_test.cc** - NO CHANGES NEEDED
**Status:** ✅ Works as-is

Simple test for ComponentArray using basic types.

---

### 6. **system_test.cc** - MAJOR REWRITE NEEDED
**Status:** ❌ Broken (calls private methods and uses undefined `TestContext::Entity`)

**Problems:**
1. Uses `TestContext::Entity` which is undefined - should be `ECS::Entity`
2. Calls `set_entities()` - this is `protected`, should not be called directly from tests
3. Calls `add_entity_()` and `remove_entity_()` - these are `private` and only for SystemManager (friend class)

**What to do:**
- Remove tests that call `set_entities()`, `add_entity_()`, `remove_entity_()`
- Keep tests that use public API: `get_entities()`, `has_entity()`
- Replace `TestContext::Entity` with `ECS::Entity`

**Tests to REMOVE:**
- `AddEntity` - calls `add_entity_()`
- `RemoveEntity` - calls `remove_entity_()`

**Tests to KEEP (with fixes):**
- `SetGetEntities` - but remove `set_entities()` call OR move test to system_manager_test
- `SetEntitiesOverwritesPrevious` - same issue
- `SetEntitiesEmpty` - same issue
- `GetEntitiesInitiallyEmpty` ✓ Already fine
- `HasEntity` - has `set_entities()` call that needs special handling

**Recommendation:** Either:
A) Move these tests to system_manager_test.cc where you test via SystemManager
B) Remove tests that require private method calls

---

### 7. **system_manager_test.cc** - MAJOR REWRITE NEEDED
**Status:** ❌ Broken (calls private System methods directly)

**Problems:**
1. Directly calls `system->add_entity_()` (private method)
2. Directly calls `system->remove_entity_()` (private method)

**What to do:**
- These methods are private for a reason - SystemManager should manage them
- Rewrite tests to use SystemManager's public API: `EntitySignatureChanged()`, `EntityDestroyed()`
- The system's entity set should be modified through these public calls, not by directly calling private methods

**Tests to REWRITE:**
- `EntityDestroyed` - currently manually adds entities with `add_entity_()`, should use `EntitySignatureChanged()` instead
- `EntityDestroyedWithMultipleSystems` - same issue
- `EntitySignatureChangedAddAndRemoveEntity` - Already uses `EntitySignatureChanged()` which is correct

**Pattern fix:**
```cpp
// OLD (wrong):
system->add_entity_(1);
system->add_entity_(2);

// NEW (correct):
test_system_manager.EntitySignatureChanged(1, ECS::Signature(0b01));
test_system_manager.EntitySignatureChanged(2, ECS::Signature(0b01));
```

---

## Summary of Changes per File

| File | Status | Changes | Severity |
|------|--------|---------|----------|
| context_test.cc | ❌ Broken | Complete rewrite | Critical |
| entity_manager_test.cc | ⚠️ Needs Fix | Replace kMaxEntities references | Major |
| component_manager_test.cc | ✅ OK | None | - |
| coordinator_test.cc | ✅ OK | None | - |
| component_array_test.cc | ✅ OK | None | - |
| system_test.cc | ❌ Broken | Remove private method tests | Major |
| system_manager_test.cc | ❌ Broken | Remove private method calls | Critical |

---

## Step-by-Step Fix Process

1. **First:** Fix `context_test.cc` - test the macro configuration directly
2. **Second:** Fix `entity_manager_test.cc` - update kMaxEntities references
3. **Third:** Fix `system_test.cc` - remove/rewrite private method tests
4. **Fourth:** Fix `system_manager_test.cc` - use public API instead of calling private methods
5. **Verify:** `component_manager_test.cc` and `coordinator_test.cc` (should already work)
6. **Confirm:** `component_array_test.cc` (should already work)

---

## Key Type Changes Reference

```cpp
// The types are now direct, not templated:
ECS::Entity              // uint8_t, uint16_t, uint32_t, or uint64_t
ECS::ComponentTypeId     // uint8_t, uint16_t, or uint32_t  
ECS::Signature           // std::bitset<ECS_MAX_COMPONENT_TYPES>

// Constants:
ECS::kMaxComponentTypes  // ECS_MAX_COMPONENT_TYPES value

// NOT AVAILABLE (removed):
ECS::kMaxEntities        // Use std::numeric_limits<ECS::Entity>::max() instead
TestContext::Entity      // Use ECS::Entity directly
ECS::Context<>           // Template-based Context no longer exists
```

