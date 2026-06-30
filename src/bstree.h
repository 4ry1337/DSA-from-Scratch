#ifndef BINARY_SEARCH_TREE_H_
#define BINARY_SEARCH_TREE_H_

#include <functional>
#include <iostream>
#include <memory>
#include <ostream>

namespace dsa {
template <typename Comparable, typename Comparator = std::less<Comparable>>
class BSTree {
 public:
  BSTree();
  BSTree(const BSTree& rhs);
  BSTree(BSTree&& rhs) noexcept;
  BSTree& operator=(const BSTree& rhs);
  BSTree& operator=(BSTree&& rhs) noexcept;
  ~BSTree();

  const Comparable& min() const { return min(root); };
  const Comparable& max() const { return max(root); };
  bool contains(const Comparable& key) const { return contains(root, key); };
  [[nodiscard]] bool empty() const;
  void print(std::ostream& out = std::cout) const { print(root, out); }

  void insert(const Comparable& key) { insert(root, key); };
  void insert(Comparable&& key) { insert(root, std::move(key)); };
  void remove(const Comparable& key) { remove(root, key); };

 private:
  struct Node {
    Comparable* item;
    Node* left;
    Node* right;

    Node(const Comparable& item, Node* left, Node* right)
        : item(new Comparable(item)), left(left), right(right) {}
    Node(Comparable&& item, Node* left, Node* right)
        : item(new Comparable(std::move(item))), left(left), right(right) {}
    Node(const Node& rhs) : Node(*rhs.item, rhs.left, rhs.right) {}
    Node(Node&& rhs) noexcept
        : item(rhs.item), left(rhs.left), right(rhs.right) {
      rhs.item = nullptr;
      rhs.left = nullptr;
      rhs.right = nullptr;
    }
    Node& operator=(const Node& rhs) {
      Node copy = rhs;
      std::swap(*this, copy);
      return *this;
    }
    Node& operator=(Node&& rhs) noexcept {
      std::swap(item, rhs.item);
      std::swap(left, rhs.left);
      std::swap(right, rhs.right);
      return *this;
    }
    ~Node() {
      delete item;
      delete left;
      delete right;
    }
  };
  std::unique_ptr<Node> root;
  Comparator less_than;
  void insert(Node*& t, const Comparable& key) {
    while (t != nullptr) {
      if (less_than(key, *t->item)) {
        t = t->left;
      } else if (less_than(*t->item, key)) {
        t = t->right;
      }
    }
    t = new Node(key, nullptr, nullptr);
  };
  void insert(Node*& t, Comparable&& key) {
    while (t != nullptr) {
      if (less_than(key, *t->item)) {
        t = t->left;
      } else if (less_than(*t->item, key)) {
        t = t->right;
      }
    }
    t = new Node(std::move(key), nullptr, nullptr);
  };
  void remove(Node*& t, const Comparable& key);
  Node* min(Node* t) const {
    if (t != nullptr) {
      while (t->left != nullptr) {
        t = t->left;
      }
    }
    return t;
  };
  Node* max(Node* t) const {
    if (t != nullptr) {
      while (t->right != nullptr) {
        t = t->right;
      }
    }
    return t;
  };
  bool contains(Node* t, const Comparable& key) const {
    /* if (t == nullptr) {
      return false;
    }

    if (key < t->item) {
      return contains(t->left, key);
    } else if (key > t->item) {
      return contains(t->right, key);
    } else {
      return true;
    } */
    while (t != nullptr) {
      if (less_than(key, *t->item)) {
        t = t->left;
      } else if (less_than(*t->item, key)) {
        t = t->right;
      } else {
        return true;
      }
    }
    return false;
  }
  void print(Node*& t, std::ostream& out) const;
  Node* clone(Node* t) const;
};
}  // namespace dsa

#endif  // !BINARY_SEARCH_TREE_H_
