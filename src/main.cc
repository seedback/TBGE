#include <iostream>
#include <limits>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/log/initialize.h"

// #include "src/ecs/ecs.h"
#include "src/ecs/context.h"
#include "src/ecs/component_array.h"

// ECS::Coordinator gCoordinator;

struct TestComponent {
  int value;
};

int main() {
  using Context = ECS::Context<>;
  ECS::ComponentArray<TestComponent, Context> component_array;

  Context::Entity entity = 1;
  TestComponent component{42};
  component_array.InsertData(entity, component);

  std::cout << "END" << std::endl;

  return 0;
}