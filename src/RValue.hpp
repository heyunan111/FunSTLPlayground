#pragma once
#include <type_traits>
namespace hyn {

template <typename T> decltype(auto) move(T &&rhs) {
  return static_cast<std::remove_reference_t<T> &&>(rhs);
}

template <typename T>
[[nodiscard]] constexpr T &&
forward(typename std::remove_reference_t<T>::type &rhs) noexcept {
  return static_cast<T &&>(rhs);
}
} // namespace hyn
