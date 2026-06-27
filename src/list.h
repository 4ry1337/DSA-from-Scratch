#ifndef LIST_H_
#define LIST_H_

#include <cstddef>
#include <utility>

namespace dsa {
template <typename Item> class List {
private:
  struct Node {
    Item data;
    Node *prev;
    Node *next;

    Node(const Item &val = Item{}, Node *prev = nullptr, Node *next = nullptr)
        : data(val), prev(prev), next(next) {}

    Node(Item &&val, Node *prev = nullptr, Node *next = nullptr)
        : data(std::move(val)), prev(prev), next(next) {}
  };
  Node m_head;
  Node m_tail;
  std::size_t m_size;

  void init() {
    m_size = 0;
    m_head = new Node;
    m_tail = new Node;
    m_head.next = m_tail;
    m_tail.prev = m_head;
  };

public:
  class const_iterator {
  protected:
    const List<Item> *p_list;
    Node *p_current;
    Item &retrieve() const { return p_current->data; }
    // why & in list?
    const_iterator(const List<Item> &p_list, Node *p)
        : p_list(&p_list), p_current(p) {}
    bool assert_is_valid() {
      if (p_list == nullptr || p_current == nullptr ||
          p_current == p_list->m_head || p_current == p_list->m_tail) {
        throw IteratorOutOfBoundsException{};
      }
    }
    friend class List<Item>;

  public:
    const_iterator() : p_current(nullptr) {}
    const Item &operator*() const { return retrieve(); }
    const_iterator &operator++() {
      p_current = p_current->next;
      return *this;
    }
    const_iterator operator++(int) {
      const_iterator old = *this;
      ++(*this);
      return old;
    }
    bool operator==(const const_iterator &rhs) {
      return p_current == rhs.p_current;
    }
    bool operator!=(const const_iterator &rhs) {
      return p_current != rhs.p_current;
    }
  };
  class iterator : public const_iterator {
  protected:
    iterator(Node *p) : const_iterator(p) {}
    friend class List<Item>;

  public:
    iterator() {};
    Item &operator*() { return const_iterator::retrieve(); }
    const Item operator*() const { return const_iterator::retrieve(); }
    iterator &operator++() {
      this->p_current = this->p_current->next;
      return *this;
    }
    iterator &operator++(int) {
      iterator old = *this;
      ++(*this);
      return old;
    }
  };

  /**
   * [begin, end)
   * */
  iterator begin() { return *m_head->next; };
  const_iterator begin() const { return *m_head->next; };
  iterator end() { return *m_tail; };
  const_iterator end() const { return *m_tail; };

  iterator insert(iterator it, const Item &data) {
    Node *curr = it.p_current;
    m_size++;
    return {curr->prev = curr->prev->next = new Node{data, curr->prev, curr}};
  }
  iterator insert(iterator it, Item &&data) {
    Node *curr = it.p_current;
    m_size++;
    return {curr->prev = curr->prev->next =
                new Node{std::move(data), curr->prev, curr}};
  }
  iterator erase(iterator it) {
    Node *remove = it.p_current;
    iterator next = remove->next;
    remove->prev->next = remove->next;
    remove->next->prev = remove->prev;
    delete remove;
    m_size--;
    return next;
  };
  iterator erase(iterator from, iterator to) {
    for (iterator it = from; it != to; ++it) {
      it = erase(it);
    }
    return to;
  };

public:
  /**
   * Constructor
   **/
  explicit List() { init(); };
  /**
   * Destructor
   **/
  ~List() {
    clear();
    delete m_head;
    delete m_tail;
  };
  /**
   * copy constructor
   **/
  List(const List &rhs) {
    init();
    for (auto &x : rhs) {
      push_back(x);
    }
  };
  /**
   * move constructor
   **/
  List(List &&rhs)
      : m_size{rhs.m_size}, m_head{rhs.m_head}, m_tail{rhs.m_tail} {
    rhs.m_head = nullptr;
    rhs.m_tail = nullptr;
    rhs.m_size = 0;
  };
  /**
   * copy assignment operator
   **/
  List &operator=(const List &rhs) {
    List copy = rhs;
    std::swap(*this, copy);
    return *this;
  };
  /**
   * move assignment operator
   **/
  List &operator=(List &&rhs) {
    std::swap(this->m_head, rhs.m_head);
    std::swap(this->m_tail, rhs.m_tail);
    std::swap(this->m_size, rhs.m_size);
    return *this;
  }

public:
  std::size_t size() const { return m_size; }
  bool empty() const { return m_size == 0; }
  void clear() {
    while (!empty()) {
      pop_front();
    }
  }

public:
  Item &front() { return *begin(); };
  const Item &front() const { return *begin(); };
  Item &back() { return *--end(); };
  const Item &back() const { return *--end(); };
  void push_front(const Item &data) { insert(begin(), data); };
  void push_front(Item &&data) { insert(begin(), data); };
  void push_back(const Item &data) { insert(end(), data); };
  void push_back(Item &&data) { insert(end(), data); };
  void pop_front() { erase(begin()); };
  void pop_back() { erase(--end()); };
};

} // namespace dsa

#endif // !LIST_H_
