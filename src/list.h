#ifndef LIST_H_
#define LIST_H_

#include <cstddef>
#include <utility>

namespace dsa {
template <typename Item> class List {
private:
  struct Node {
    Item val;
    Node *prev;
    Node *next;
  };
  Node head;
  Node tail;
  void init();

public:
  class const_iterator {};
  class iterator : public const_iterator {};

public:
  /**
   * Constructor
   **/
  explicit List();
  /**
   * Destructor
   **/
  ~List();
  /**
   * copy constructor
   **/
  List(const List &rhs);
  /**
   * move constructor
   **/
  List(List &&rhs);
  /**
   * copy assignment operator
   **/
  List &operator=(const List &rhs);
  /**
   * move assignment operator
   **/
  List &operator=(List &&rhs);

public:
  std::size_t size() const;
  bool empty() const;
  void clear();

public:
  Item &front();
  const Item &front() const;
  Item &back();
  const Item &back() const;
  void push_front(const Item &val);
  void push_front(Item &&val);
  void push_back(const Item &val);
  void push_back(Item &&val);
  void pop_front();
  void pop_back();

public:
  iterator begin();
  const_iterator begin() const;
  iterator end();
  const_iterator end() const;
  iterator insert(iterator it, const Item &val);
  iterator insert(iterator it, Item &&val);
  iterator erase(iterator it);
  iterator erase(iterator from, iterator to);
};

} // namespace dsa

#endif // !LIST_H_
