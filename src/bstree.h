#ifndef BINARY_SEARCH_TREE_H_
#define BINARY_SEARCH_TREE_H_

#include <iostream>
#include <memory>
#include <ostream>
namespace dsa {
template <typename Comparable>
class BSTree {
 public:
  BSTree();
  BSTree(const BSTree& rhs);
  BSTree(BSTree&& rhs) noexcept;
  BSTree& operator=(const BSTree& rhs);
  BSTree& operator=(BSTree&& rhs) noexcept;
  ~BSTree();

  const Comparable& min() const;
  const Comparable& max() const;
  bool contains(const Comparable& key) const;
  [[nodiscard]] bool empty() const;
  void print(std::ostream& out = std::cout) const;

  void insert(const Comparable& key);
  void insert(Comparable&& key);
  void remove(const Comparable& key);

 private:
  struct Node {
    std::unique_ptr<Comparable> item;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
  };
  std::unique_ptr<Node> root;
  void insert(const Comparable& key, Node*& t);
  void insert(Comparable&& key, Node*& t);
  void remove(const Comparable& key, Node*& t);
};

}  // namespace dsa

#endif  // !BINARY_SEARCH_TREE_H_
