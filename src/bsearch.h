#ifndef BSEARCH_H_
#define BSEARCH_H_

#include "result.h"
#include "vector.h"
#include <cstddef>

namespace dsa {

template <typename Comparable>
Result<std::size_t, std::size_t> binary_search(const Vector<Comparable> &vec, const Comparable &q) {
    if (vec.size() == 0) {
        return Result<std::size_t, std::size_t>::err(0);
    }

    std::size_t size = vec.size();
    std::size_t base = 0;

    while (size > 1) {
        std::size_t half = size / 2;
        std::size_t mid = base + half;
        if (vec[mid] == q) {
            return Result<std::size_t, std::size_t>::ok(mid);
        } else if (q > vec[mid]) {
            base = mid;
        }
        size -= half;
    }

    if (vec[base] == q) {
        return Result<std::size_t, std::size_t>::ok(base);
    }
    return Result<std::size_t, std::size_t>::err(base + (vec[base] < q));
}

} // namespace dsa

#endif // !BSEARCH_H_
