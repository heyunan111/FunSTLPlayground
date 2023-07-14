#pragma once

#include <iostream>
#include <memory>
#include <typeinfo>

namespace hyn {

// 使用any_cast时发生异常
class bad_any_cast : public std::bad_cast {
public:
  const char *what() const noexcept override {
    return "bad any cast: failed conversion using hyn::any_cast";
  }
};

class any {
public:
  constexpr any() = default;
  ~any() = default;

  any(const any &) = delete;
  any &operator=(const any &) = delete;

  any(any &&) = default;
  any &operator=(any &&) = default;

  template <typename T> any(T data) : ptr_(std::make_unique<derive<T>>(data)) {}

  void reset() noexcept { ptr_.reset(); }

  void swap(any &rhs) noexcept { ptr_.swap(rhs.ptr_); }

private:
  class base {
  public:
    virtual ~base() = default;
  };

  template <typename T> class derive {
  public:
    derive(T data) : data_(data) {}

    T data_;
  };

private:
  std::unique_ptr<base> ptr_;
};

void swap(any &lhs, any &rhs) { lhs.swap(rhs); }

} // namespace hyn