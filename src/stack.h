#ifndef STACK_H_
#define STACK_H_

#include <cstddef>

#include "vector.h"

namespace dsa {
template <typename Item>
class Stack {
 private:
  Vector<Item> m_data;

 public:
  explicit Stack() : m_data(Vector<Item>{}) {};
  Stack(std::initializer_list<Item> items) : Stack() {
    for (const Item& item : items) {
      m_data.push_back(item);
    }
  };
  ~Stack() = default;
  Stack(const Stack& rhs) : m_data(rhs.m_data) {}
  Stack(Stack&& rhs) noexcept : m_data(std::move(rhs.m_data)) {}
  Stack& operator=(const Stack& rhs) {
    if (this == &rhs) {
      return *this;
    }
    Stack copy = rhs;
    std::swap(*this, copy);
    return *this;
  }
  Stack& operator=(Stack&& rhs) noexcept {
    std::swap(m_data, rhs.m_data);
    return *this;
  }
  void push(const Item& item) { m_data.push_back(item); };
  void push(Item&& item) { m_data.push_back(std::move(item)); };
  void pop() { m_data.pop_back(); };
  Item& top() { return m_data.back(); };
  [[nodiscard]] const Item& top() const { return m_data.back(); };
  [[nodiscard]] std::size_t size() { return m_data.size(); }
  [[nodiscard]] bool empty() { return m_data.empty(); }
};
}  // namespace dsa

#endif  // !STACK_H_
