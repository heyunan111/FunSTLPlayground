#pragma once

#include <cstddef>
#include <iostream>
#include <memory>
#include <typeinfo>

namespace hyn {

class bad_any_cast : public std::bad_cast {
public:
  virtual const char *what() const noexcept { return "类型不匹配"; }
};

class any {
  class base_ {
  public:
    virtual ~base_() = default;
  };

  template <typename T> class derive_ : public base_ {
  public:
    derive_(T data) : data_(data) {}
    T data_;
  };

public:
  any() = default;
  ~any() = default;

  any(const any &) = delete;

  any &operator=(const any &) = delete;

  template <typename T>
  any(T data) : ptr_(std::make_unique<derive_<T>>(data)) {}

  any(any &&) = default;

  any &operator=(any &&) = default;

  template <typename T> T _Cast() {
    auto *p = dynamic_cast<derive_<T> *>(ptr_.get());
    if (p == nullptr)
      throw bad_any_cast{};
    return p->data_;
  }

private:
  std::unique_ptr<base_> ptr_;
};

template <typename T> T any_cast(any &rhs) { return rhs._Cast<T>(); }

} // namespace hyn

struct A {
  A(int a) : s(a) {}
  int s;
};

void any_test() {
  hyn::any a(12);
  std::cout << hyn::any_cast<int>(a) << std::endl;
  hyn::any b(3.14);
  std::cout << hyn::any_cast<double>(b) << std::endl;
  A aa(2);
  hyn::any c(aa);
  std::cout << hyn::any_cast<A>(c).s << std::endl;
}