#ifndef LIST_H_
#define LIST_H_

#include <cstddef>
#include <gsl/pointers>

namespace dsa {

struct IteratorOutOfBoundsException : public std::exception {
    [[nodiscard]] const char *what() const noexcept override { return "iterator out of bounds"; }
};

struct IteratorMismatchException : public std::exception {
    [[nodiscard]] const char *what() const noexcept override { return "iterator list mismatch"; }
};

template <typename Item> class List {
  private:
    struct Node {
        Item m_data;
        Node *m_prev;
        Node *m_next;

        Node(const Item &val = Item{}, Node *prev = nullptr, Node *next = nullptr) // NOLINT
            : m_data(val), m_prev(prev), m_next(next) {}

        Node(Item &&val, Node *prev = nullptr, Node *next = nullptr) // NOLINT
            : m_data(std::move(val)), m_prev(prev), m_next(next) {}
    };
    gsl::owner<Node *> m_head;
    gsl::owner<Node *> m_tail;
    std::size_t m_size{};

  public:
    /**
     * Constructor
     **/
    explicit List() : m_head(new Node), m_tail(new Node) {
        m_head->m_next = m_tail;
        m_tail->m_prev = m_head;
    };
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
    List(const List &rhs) : List() {
        for (auto &x : rhs) {
            push_back(x);
        }
    };
    /**
     * move constructor
     **/
    List(List &&rhs) noexcept
        : m_head{rhs.m_head}, m_tail{rhs.m_tail}, // NOLINT(cppcoreguidelines-owning-memory)
          m_size{rhs.m_size} {                    // NOLINT(cppcoreguidelines-owning-memory)
        rhs.m_head = nullptr;                     // NOLINT(cppcoreguidelines-owning-memory)
        rhs.m_tail = nullptr;                     // NOLINT(cppcoreguidelines-owning-memory)
        rhs.m_size = 0;
    }
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
    List &operator=(List &&rhs) noexcept {
        std::swap(m_head, rhs.m_head);
        std::swap(m_tail, rhs.m_tail);
        std::swap(m_size, rhs.m_size);
        return *this;
    }

  public:
    [[nodiscard]] std::size_t size() const { return m_size; }
    [[nodiscard]] bool empty() const { return m_size == 0; }
    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

  public:
    [[nodiscard]] Item &front() { return *begin(); };
    [[nodiscard]] const Item &front() const { return *begin(); };
    [[nodiscard]] Item &back() { return *--end(); };
    [[nodiscard]] const Item &back() const { return *--end(); };
    void push_front(const Item &data) { insert(begin(), data); };
    void push_front(Item &&data) { insert(begin(), std::move(data)); };
    void push_back(const Item &data) { insert(end(), data); };
    void push_back(Item &&data) { insert(end(), std::move(data)); };
    void pop_front() { erase(begin()); };
    void pop_back() { erase(--end()); };

  public:
    class const_iterator {
      private:
        const List<Item> *p_list;
        Node *p_current;

      protected:
        friend class List<Item>;
        [[nodiscard]] Item &retrieve() const { return p_current->m_data; }
        [[nodiscard]] const_iterator(const List<Item> &p_list, Node *p)
            : p_list(&p_list), p_current(p) {}

        void assert_is_valid() {
            if (p_list == nullptr || p_current == nullptr || p_current == p_list->m_head) {
                throw IteratorOutOfBoundsException{};
            }
        }

      public:
        const_iterator() : p_current(nullptr) {}
        const Item &operator*() const { return retrieve(); }
        const_iterator &operator++() {
            p_current = p_current->m_next;
            return *this;
        }
        const_iterator operator++(int) {
            const_iterator old = *this;
            ++(*this);
            return old;
        }
        const_iterator &operator--() {
            this->p_current = this->p_current->m_prev;
            return *this;
        }
        const_iterator operator--(int) {
            iterator old = *this;
            --(*this);
            return old;
        }
        bool operator==(const const_iterator &rhs) { return p_current == rhs.p_current; }
        bool operator!=(const const_iterator &rhs) { return p_current != rhs.p_current; }
    };
    class iterator : public const_iterator {
      protected:
        iterator(const List<Item> &p_list, Node *p_current) : const_iterator(p_list, p_current) {}
        friend class List<Item>;

      public:
        iterator() = default;
        Item &operator*() { return const_iterator::retrieve(); }
        const Item operator*() const { return const_iterator::operator*(); }
        iterator &operator++() {
            this->p_current = this->p_current->m_next;
            return *this;
        }
        iterator operator++(int) {
            iterator old = *this;
            ++(*this);
            return old;
        }
        iterator &operator--() {
            this->p_current = this->p_current->m_prev;
            return *this;
        }
        iterator operator--(int) {
            iterator old = *this;
            --(*this);
            return old;
        }
    };

    /**
     * [begin, end)
     * */
    iterator begin() { return iterator(*this, m_head->m_next); };
    [[nodiscard]] const_iterator begin() const { return const_iterator(*this, m_head->m_next); };
    iterator end() { return iterator(*this, m_tail); };
    [[nodiscard]] const_iterator end() const { return const_iterator(*this, m_tail); };

    iterator insert(iterator it, const Item &data) {
        it.assert_is_valid();
        if (it.p_list != this) {
            throw IteratorMismatchException{};
        }
        Node *curr = it.p_current;
        m_size++;
        return {*this, curr->m_prev = curr->m_prev->m_next =
                           gsl::owner<Node *>{new Node{std::move(data), curr->m_prev, curr}}};
    }
    iterator insert(iterator it, Item &&data) {
        it.assert_is_valid();
        if (it.p_list != this) {
            throw IteratorMismatchException{};
        }
        Node *curr = it.p_current;
        m_size++;
        return {*this, curr->m_prev = curr->m_prev->m_next =
                           gsl::owner<Node *>{new Node{std::move(data), curr->m_prev, curr}}};
    }
    iterator erase(iterator it) {
        it.assert_is_valid();
        if (it.p_list != this) {
            throw IteratorMismatchException{};
        }
        gsl::owner<Node *> remove = it.p_current; // NOLINT(cppcoreguidelines-owning-memory)
        ++it;
        remove->m_prev->m_next = remove->m_next;
        remove->m_next->m_prev = remove->m_prev;
        delete remove;
        m_size--;
        return it;
    };
    iterator erase(iterator from, iterator to) {
        from.assert_is_valid();
        to.assert_is_valid();
        if (from.p_list != this || to.p_list != this) {
            throw IteratorMismatchException{};
        }
        for (iterator it = from; it != to;) {
            it = erase(it);
        }
        return to;
    };
};

} // namespace dsa

#endif // !LIST_H_
