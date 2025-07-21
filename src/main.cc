#include <iostream>
#include <limits>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/log/initialize.h"

#include "src/ecs/ecs.h"

ECS::Coordinator gCoordinator;

int main() {
  absl::InitializeLog();
  LOG(ERROR) << "test";
  std::cout << "Hello, World!" << std::endl;
  std::cout << "max entities " << ECS::kMaxEntities << std::endl;
  std::cout << int(std::numeric_limits<ECS::Entity>::max()) << std::endl;
  return 0;
}