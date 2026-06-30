#ifndef FIND_H_
#define FIND_H_

namespace dsa {
template <typename Iterator, typename Item>
Iterator find(Iterator start, Iterator end, const Item& key) {
  for (Iterator it = start; it != end; ++it) {
    if (*it == key) {
      return it;
    }
  }
  return end;
};
}  // namespace dsa

#endif  // !FIND_H_
