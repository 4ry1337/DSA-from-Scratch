#ifndef BSEARCH_H_
#define BSEARCH_H_

#include <cstddef>
#include <optional>
#include <vector>

namespace dsa {

template <typename Comparable>
std::optional<std::size_t> binary_search(const std::vector<Comparable> &vec,
                                         const Comparable &q) {
  if (vec.size() == 0)
    return std::nullopt;

  std::size_t low = 0, high = vec.size() - 1;

  while (low <= high) {
    std::size_t mid = low + (high - low) / 2;
    if (vec[mid] > q) {
      high = mid - 1;
    } else if (vec[mid] < q) {
      low = mid + 1;
    } else {
      return std::make_optional(mid);
    }
  }

  return std::nullopt;
}

} // namespace dsa

#endif // !BSEARCH_H_
