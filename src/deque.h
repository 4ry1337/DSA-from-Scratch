#ifndef DEQUE_H_

#define DEQUE_H_

#include <cstddef>
#include <initializer_list>

#include "list.h"
#include "vector.h"

namespace dsa {
template <typename Item>
class Deque {
 private:
  List<Vector<Item>> m_data;
  std::size_t front{};
  [[nodiscard]] bool full(const Vector<Item>& vec) {
    return vec.size() == vec.capacity();
  }

 public:
  Deque() { m_data.push_back(Vector<Item>{}); }
  Deque(std::initializer_list<Item> items) : Deque() {
    for (const Item& item : items) {
      enqueue(item);
    }
  }
  ~Deque() = default;
  Deque(const Deque& rhs) : Deque() {
    for (std::size_t i = 0; i < rhs.size(); ++i) {
      enqueue(rhs[i]);
    }
  };
  Deque(Deque&& rhs) noexcept
      : m_data(std::move(rhs.m_data)), front(rhs.front) {
    rhs.front = 0;
  };
  Deque& operator=(const Deque& rhs) {
    Deque copy = rhs;
    std::swap(*this, copy);
    return *this;
  };
  Deque& operator=(Deque&& rhs) noexcept {
    std::swap(m_data, rhs.m_data);
    std::swap(front, rhs.front);
    return *this;
  };

  void enqueue(const Item& item) {
    if (full(m_data.back())) {
      m_data.push_back(Vector<Item>{});
    }
    m_data.back().push_back(item);
  };
  void enqueue(Item&& item) {
    if (full(m_data.back())) {
      m_data.push_back(Vector<Item>{});
    }
    m_data.back().push_back(std::move(item));
  };
  Item dequeue() {
    Item old = m_data.front()[front++];
    if (front == m_data.front().size() && m_data.size() > 1) {
      m_data.pop_front();
      front = 0;
    }
    return old;
  };

  Item& operator[](std::size_t index) {
    std::size_t adjusted = front + index;
    std::size_t offset = adjusted / Vector<Item>::DEFAULT_SIZE;
    std::size_t i = adjusted % Vector<Item>::DEFAULT_SIZE;
    auto itr = m_data.begin();
    for (std::size_t k = 0; k < offset; ++k) {
      ++itr;
    }
    return (*itr)[i];
  }

  /** Returns a const reference to the element at `index`. No bounds checking.
   */
  const Item& operator[](std::size_t index) const {
    std::size_t adjusted = front + index;
    std::size_t offset = adjusted / Vector<Item>::DEFAULT_SIZE;
    std::size_t i = adjusted % Vector<Item>::DEFAULT_SIZE;
    auto itr = m_data.begin();
    for (std::size_t k = 0; k < offset; ++k) {
      ++itr;
    }
    return (*itr)[i];
  }

  [[nodiscard]] std::size_t size() const {
    return (m_data.size() - 1) * Vector<Item>::DEFAULT_SIZE +
           m_data.back().size() - front;
  }
  [[nodiscard]] bool empty() const { return size() == 0; }
};
}  // namespace dsa

#endif  // !DEQUE_H_
