#include <iostream>
#include <limits>

#include "src/ecs/ecs.h"

ECS::Coordinator gCoordinator;

int main() {
  std::cout << "Hello, World!" << std::endl;
  std::cout << "max entities " << ECS::kMaxEntities << std::endl;
  std::cout << int(std::numeric_limits<ECS::Entity>::max()) << std::endl;
  return 0;
}