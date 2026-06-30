#ifndef RESULT_H_
#define RESULT_H_

#include <stdexcept>
#include <utility>
#include <variant>

namespace dsa {
template <typename T, typename E>
class Result {
  struct Ok {};
  struct Err {};

  std::variant<T, E> m_data;
  explicit Result(Ok, T p_val)
      : m_data(std::in_place_index<0>, std::move(p_val)) {};
  explicit Result(Err, E p_error)
      : m_data(std::in_place_index<1>, std::move(p_error)) {};

 public:
  static Result ok(T val) { return Result(Ok{}, std::move(val)); }
  static Result err(E err) { return Result(Err{}, std::move(err)); }

  [[nodiscard]] bool is_ok() const { return m_data.index() == 0; }
  [[nodiscard]] bool is_err() const { return m_data.index() == 1; }

  T& unwrap() {
    if (is_err()) {
      throw std::runtime_error("called unwrap on Err");
    }
    return std::get<0>(m_data);
  }

  E& unwrap_err() {
    if (is_ok()) {
      throw std::runtime_error("called unwrap_err on Ok");
    }
    return std::get<1>(m_data);
  }

  template <typename F>
  auto map(F&& f) -> Result<std::invoke_result_t<F, T>, E> {
    if (is_ok()) {
      return Result<std::invoke_result_t<F, T>, E>::ok(
          std::forward<F>(f)(std::get<0>(m_data)));
    }
    return Result<std::invoke_result_t<F, T>, E>::err(std::get<1>(m_data));
  }

  [[nodiscard]] T unwrap_or(T fallback) const {
    return is_ok() ? std::get<0>(m_data) : std::move(fallback);
  }
};
}  // namespace dsa

#endif  // !RESULT_H_
