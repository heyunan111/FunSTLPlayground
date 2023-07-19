#pragma once
#include <type_traits>

namespace hyn {

template <typename T> class new_allocator {
public:
  using value_type = T;
  using pointer = T *;
  using const_pointer = const T *;
  using void_pointer = void *;
  using const_void_pointer = const void *;
  using size_type = size_t;
  using difference_type = std::ptrdiff_t;

  new_allocator() = default;
  ~new_allocator() = default;

  pointer allocator(size_type numObj) {
    return static_cast<pointer>(operator new(sizeof(T) * numObj));
  }

  void deallocator(pointer p, size_type numObj) { operator delete(p); }

  template <typename U, typename... Args> void construct(U *p, Args &&...args) {
    new (p) U(std::forward<Args>(args)...);
  }

  template <typename U> void destroy(U *p) { p->~U(); }

  template <typename _TP> struct rebind {
    using other = new_allocator<_TP>;
  };
};

} // namespace hyn