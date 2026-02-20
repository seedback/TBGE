# ECS Test Migration - Quick Reference Guide

## What Changed

The ECS system moved from **template-based configuration** to **macro-based configuration**.

### At a Glance

| Aspect | Old (Template) | New (Macro-Based) |
|--------|---|---|
| **Entity Type** | Template parameter | `ECS::Entity` (direct type) |
| **Component Type ID** | Template parameter | `ECS::ComponentTypeId` (direct type) |
| **Configuration** | Via template specialization | Via preprocessor macros |
| **Max Entities** | `ECS::kMaxEntities` | `std::numeric_limits<ECS::Entity>::max()` |
| **Max Component Types** | `ECS::kMaxComponentTypes` | `ECS::kMaxComponentTypes` (constant) |
| **Test Helper Classes** | `TestContext` template | None needed - use direct types |

---

## Common Fixes Explained

### Fix #1: Remove Template-Based Context

```cpp
// ❌ BEFORE: Using template (WRONG - doesn't exist)
using TestContext = ECS::Context<>;
using MyEntity = TestContext::Entity;
auto max = TestContext::kMaxEntities;

// ✅ AFTER: Using direct types
using MyEntity = ECS::Entity;
auto max = std::numeric_limits<ECS::Entity>::max();
```

**Where this appears:** context_test.cc (completely rewritten)

---

### Fix #2: Replace kMaxEntities References

```cpp
// ❌ BEFORE: Using non-existent constant
ECS::Entity invalid_entity = ECS::kMaxEntities;
if (entity_count >= ECS::kMaxEntities) { /* ... */ }

// ✅ AFTER: Use limit from Entity type
ECS::Entity invalid_entity = std::numeric_limits<ECS::Entity>::max();
if (entity_count >= std::numeric_limits<ECS::Entity>::max()) { /* ... */ }
```

**Where this appears:** entity_manager_test.cc

---

### Fix #3: Use Public API for System Entity Management

```cpp
// ❌ BEFORE: Calling private methods (WRONG)
system->set_entities(entities);    // protected method
system->add_entity_(entity_id);    // private method - only SystemManager can call
system->remove_entity_(entity_id); // private method - only SystemManager can call

// ✅ AFTER: Use SystemManager's public API
test_system_manager.EntitySignatureChanged(entity_id, signature);
test_system_manager.EntityDestroyed(entity_id);
```

**Where this appears:** system_test.cc, system_manager_test.cc

**Why:** The `System` class should only manage which entities it contains. The `SystemManager` is responsible for deciding when to add/remove entities based on signature matching.

---

### Fix #4: Replace TestContext::Entity with ECS::Entity

```cpp
// ❌ BEFORE: Using undefined TestContext
std::set<TestContext::Entity> entities = {1, 2, 3};

// ✅ AFTER: Use direct ECS type
std::set<ECS::Entity> entities = {1, 2, 3};
```

**Where this appears:** system_test.cc

---

## Implementation Checklist

When fixing a test file, check for these patterns:

### Checklist Item 1: Template-Based Context
- [ ] No `ECS::Context<...>` instantiations
- [ ] No `TestContext` type definitions
- [ ] No `typename Config::...` references
- [ ] No `template<typename Config>` in test code

### Checklist Item 2: Max Entities References
- [ ] No `ECS::kMaxEntities` usage
- [ ] Any entity limit checks use `std::numeric_limits<ECS::Entity>::max()`
- [ ] Comments referencing old test-specific limits are updated

### Checklist Item 3: Type References
- [ ] All entity types are `ECS::Entity` (not `TestContext::Entity`)
- [ ] All component type IDs are `ECS::ComponentTypeId`
- [ ] All signatures are `ECS::Signature`

### Checklist Item 4: System Method Calls
- [ ] No calls to `system->set_entities()`
- [ ] No calls to `system->add_entity_()`
- [ ] No calls to `system->remove_entity_()`
- [ ] Using `SystemManager::EntitySignatureChanged()` instead
- [ ] Using `SystemManager::EntityDestroyed()` instead

### Checklist Item 5: Configuration Tests
- [ ] Tests verify actual type sizes (using `sizeof`)
- [ ] Tests check macro values are correctly applied
- [ ] Tests use preprocessor conditionals for configuration-dependent code

---

## Test File Status Reference

Use this to understand which files need work:

```
✅ component_array_test.cc      - No changes needed
✅ component_manager_test.cc     - No changes needed  
✅ context_test.cc              - FIXED (complete rewrite)
✅ coordinator_test.cc          - No changes needed
✅ entity_manager_test.cc       - FIXED (invalid_entity handling)
✅ system_manager_test.cc       - FIXED (private method calls)
✅ system_test.cc               - FIXED (removed private method calls)
```

---

## Code Pattern Examples

### Pattern: Testing Configuration

```cpp
// Test that Entity type is correct size for configured bit width
TEST(Context, EntityTypeConfiguration) {
#if ECS_ENTITY_CONFIG == 32
  EXPECT_EQ(sizeof(ECS::Entity), 4);
  EXPECT_EQ(typeid(ECS::Entity), typeid(std::uint32_t));
#elif ECS_ENTITY_CONFIG == 16
  EXPECT_EQ(sizeof(ECS::Entity), 2);
  EXPECT_EQ(typeid(ECS::Entity), typeid(std::uint16_t));
#endif
}
```

### Pattern: Testing Public API Only

```cpp
// ✅ Test only uses public API
TEST_F(SystemTest, GetEntitiesInitiallyEmpty) {
  ECS::System system;
  EXPECT_TRUE(system.get_entities().empty());  // Public method only
}

// ❌ Don't do this
TEST_F(SystemTest, BadTest) {
  ECS::System system;
  system.set_entities({1, 2, 3});  // ❌ Protected method - not allowed
  // ...
}
```

### Pattern: System Entity Management

```cpp
// ✅ Correct: Use SystemManager to manage entities
TEST_F(SystemManagerTest, EntityManagement) {
  auto system = test_system_manager.RegisterSystem<DummySystem>();
  test_system_manager.SetSignature<DummySystem>(ECS::Signature(0b1));
  
  // Add entity by changing its signature to match system's
  test_system_manager.EntitySignatureChanged(1, ECS::Signature(0b1));
  EXPECT_TRUE(system->has_entity(1));  // System now contains entity 1
  
  // Remove entity by changing its signature to not match
  test_system_manager.EntitySignatureChanged(1, ECS::Signature(0b0));
  EXPECT_FALSE(system->has_entity(1));  // Entity removed from system
}

// ❌ Wrong: Don't call private System methods
TEST_F(SystemManagerTest, BadTest) {
  auto system = test_system_manager.RegisterSystem<DummySystem>();
  system->add_entity_(1);  // ❌ Private method
  system->remove_entity_(1);  // ❌ Private method
}
```

---

## Debugging Tips

### Issue: "undefined reference to `TestContext`"
**Solution:** Replace `TestContext::Entity` with `ECS::Entity`

### Issue: "`kMaxEntities` is not a member of `ECS`"
**Solution:** Use `std::numeric_limits<ECS::Entity>::max()` instead

### Issue: Call to private method `add_entity_`
**Solution:** Use `SystemManager::EntitySignatureChanged()` instead

### Issue: Call to protected method `set_entities`
**Solution:** Remove the test or use SystemManager's public API

### Issue: Template parameter errors in context tests
**Solution:** Rewrite to test the macro-based configuration directly

---

## Quick Fix Templates

### Template 1: Fix entity_manager_test.cc

```cpp
// Step 1: Update invalid_entity
- ECS::Entity invalid_entity = 10;
+ ECS::Entity invalid_entity = std::numeric_limits<ECS::Entity>::max();

// Step 2: Fix CreateTooManyEntities test
// (Already in fixed version)
```

### Template 2: Fix system_test.cc

```cpp
// Step 1: Replace all TestContext::Entity with ECS::Entity
- std::set<TestContext::Entity> entities = {1, 2, 3};
+ std::set<ECS::Entity> entities = {1, 2, 3};

// Step 2: Remove tests calling protected/private methods
// Delete: SetGetEntities, SetEntitiesOverwritesPrevious, SetEntitiesEmpty,
//         AddEntity, RemoveEntity
// Keep: GetEntitiesInitiallyEmpty, HasEntityEmptySet

// Step 3: Rewrite tests to use only public API
```

### Template 3: Fix system_manager_test.cc

```cpp
// Step 1: Replace direct entity addition
- system->add_entity_(1);
- system->add_entity_(2);
+ test_system_manager.EntitySignatureChanged(1, ECS::Signature(0b1));
+ test_system_manager.EntitySignatureChanged(2, ECS::Signature(0b1));

// Step 2: Add verification
+ EXPECT_TRUE(system->has_entity(1));
+ EXPECT_TRUE(system->has_entity(2));
```

---

## Summary

The macro-based configuration system is **simpler** because:

1. **No templates needed** - Types are directly defined based on macros
2. **Compile-time only** - Configuration happens at preprocessor stage
3. **Type-safe** - All types are known at compile-time
4. **Public API clear** - Tests can only use public methods (better isolation)

The migration is **straightforward**:

1. Remove template specializations
2. Replace constant references with proper types/limits
3. Use public API instead of private methods
4. Test the macro-based configuration directly

---

## Files Modified

All the following test files have been fixed:

- [test/ecs/context_test.cc](test/ecs/context_test.cc) ✅
- [test/ecs/entity_manager_test.cc](test/ecs/entity_manager_test.cc) ✅
- [test/ecs/system_test.cc](test/ecs/system_test.cc) ✅
- [test/ecs/system_manager_test.cc](test/ecs/system_manager_test.cc) ✅

See [FIXES_SUMMARY.md](FIXES_SUMMARY.md) for detailed before/after comparisons.

See [TEST_MIGRATION_GUIDE.md](TEST_MIGRATION_GUIDE.md) for comprehensive migration documentation.

