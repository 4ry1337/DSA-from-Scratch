#ifndef BINARY_SEARCH_TREE_H_
#define BINARY_SEARCH_TREE_H_

#include <memory>
namespace dsa {
template <typename Comparable> class BSTree {
  private:
    struct Node {
        std::unique_ptr<Comparable> item;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
    };

  public:
    BSTree();
    ~BSTree();
    BSTree(const BSTree &rhs);
    BSTree(BSTree &&rhs) noexcept;
    BSTree &operator=(const BSTree &rhs);
    BSTree &operator=(BSTree &&rhs) noexcept;
};

} // namespace dsa

#endif // !BINARY_SEARCH_TREE_H_
