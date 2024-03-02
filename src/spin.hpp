#ifndef A2BC07F1_D7FB_4A2E_8A1A_5B866A57CFDF
#define A2BC07F1_D7FB_4A2E_8A1A_5B866A57CFDF

#include <atomic>

class spin {
public:
  void lock() {
    while (m_flag_.test_and_set(std::memory_order_acquire)) {
    }
  }

  void unlock() { m_flag_.clear(); }

private:
  std::atomic_flag m_flag_ = ATOMIC_FLAG_INIT;
};

#endif /* A2BC07F1_D7FB_4A2E_8A1A_5B866A57CFDF */
