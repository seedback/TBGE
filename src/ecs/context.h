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
template <size_t MAX_E = static_cast<size_t>(-1),
          size_t MAX_C = static_cast<size_t>(-1), typename E = std::uint16_t,
          typename C = std::uint16_t>
struct Context {
  using Entity = E;
  using ComponentTypeId = C;

  static constexpr Entity kMaxEntities = (MAX_E == static_cast<size_t>(-1))
                                             ? std::numeric_limits<E>::max()
                                             : static_cast<E>(MAX_E);
  static constexpr ComponentTypeId kMaxComponentTypes =
      (MAX_C == static_cast<size_t>(-1)) ? std::numeric_limits<C>::max()
                                         : static_cast<C>(MAX_C);

  using Signature = std::bitset<kMaxComponentTypes>;

  Context() { SetupConsoleForUnicode(); }

 private:
  void SetupConsoleForUnicode() {
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#else
    // On Linux/macOS, UTF-8 is usually the default
    // Set locale to ensure proper UTF-8 handling
    std::locale::global(std::locale(""));
    std::wcout.imbue(std::locale());
#endif  // _WIN32
  }
};

}  // namespace ECS

#endif // TBGE_SRC_ECS_CONFIG_H_