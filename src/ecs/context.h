#ifndef TBGE_SRC_ECS_CONFIG_H_
#define TBGE_SRC_ECS_CONFIG_H_

#include <bitset>
#include <cstdint>
#include <limits>

namespace ECS {
template <typename E = std::uint16_t, typename C = std::uint16_t,
          E MAX_E = std::numeric_limits<E>::max(),
          C MAX_C = std::numeric_limits<C>::max()>
struct Context {
  using Entity = E;
  using ComponentTypeId = C;
  using Signature = std::bitset<MAX_C>;

  static constexpr Entity kMaxEntities = MAX_E;
  static constexpr ComponentTypeId kMaxComponentTypes = MAX_C;
};

}  // namespace ECS

#endif