#ifndef VECTOR_H_
#define VECTOR_H_

#include <cstddef>
#include <gsl/pointers>
#include <span>

namespace dsa {

/**
 * A dynamic array
 *
 * Owns a heap-allocated contiguous buffer of `capacity` slots, of which
 * `size` are live. When the buffer is full, `push_back` doubles the capacity
 * (plus one) before inserting, so amortized push_back is O(1).
 *
 * @tparam Item  The element type stored in the vector.
 */

template <typename Item> class Vector {
  private:
    std::size_t m_size;
    std::size_t m_capacity{DEFAULT_SIZE};
    Item *m_items;

  public:
    static const std::size_t DEFAULT_SIZE = 16;
    /** Constructs a vector with `initial_size` default-initialised elements and
     *  an initial capacity of 16. */
    explicit Vector(std::size_t initial_size = 0)
        : m_size(initial_size), m_items(new Item[m_capacity]) {}

    Vector(std::initializer_list<Item> items) : Vector() {
        for (const Item &x : items) {
            push_back(x);
        }
    }

    /**
     * Copy constructor — deep copy.
     *
     * Allocates a fresh buffer of the same capacity and copies every live
     * element from `rhs` into it.  After this call, `*this` and `rhs` own
     * separate allocations; mutating one does not affect the other.
     *
     * Complexity: O(n) time and space.
     */
    Vector(Vector &rhs)
        : m_size(rhs.m_size), m_capacity(rhs.m_capacity), m_items(new Item[m_capacity]) {
        std::span<Item> view{m_items, m_size};
        std::span<Item> rhs_view{rhs.m_items, rhs.m_size};
        for (std::size_t i{}; i < view.size(); ++i) {
            view[i] = rhs_view[i];
        }
    }

    /**
     * Move constructor — ownership transfer, O(1).
     *
     * Steals the buffer pointer and bookkeeping values from `rhs`, then nulls
     * out `rhs` so its destructor calls `delete[] nullptr` (a no-op).  No
     * element copies are performed.
     *
     * After this call `rhs` is in a valid-but-empty state (size 0, capacity 0,
     * null pointer) and must not be used except to be destroyed or reassigned.
     */
    Vector(Vector &&rhs) noexcept
        : m_size(rhs.m_size), m_capacity(rhs.m_capacity), m_items(rhs.m_items) {
        rhs.m_items = nullptr;
        rhs.m_size = 0;
        rhs.m_capacity = 0;
    }

    /**
     * Copy assignment operator — copy-and-swap idiom.
     *
     * Constructs a temporary deep copy of `rhs` (via the copy constructor),
     * then swaps its internals with `*this`.  The old buffer of `*this` is
     * released when the temporary goes out of scope.
     *
     * This idiom is self-assignment safe: if `&rhs == this`, the copy is made
     * first and the swap is a no-op.
     *
     * Complexity: O(n) — same as copy construction.
     */
    Vector &operator=(const Vector &rhs) {
        if (this == &rhs) {
            return *this;
        }
        Vector copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    /**
     * Destructor — releases the owned buffer.
     *
     * The only resource managed by Vector is the heap array `m_items`.
     * `delete[] nullptr` is defined to be a no-op, so a moved-from Vector
     * (whose pointer was nulled out) is safe to destroy.
     */
    ~Vector() { delete[] m_items; }

    /**
     * Move assignment operator — swap internals, O(1).
     *
     * Swaps all three members with `rhs`.  The old resources of `*this` end up
     * in `rhs` and will be released when `rhs` is destroyed (typically at the
     * end of the statement that triggered the move).
     *
     * Handles self-assignment correctly: swapping with yourself is a no-op.
     */
    Vector &operator=(Vector &&rhs) noexcept {
        std::swap(m_size, rhs.m_size);
        std::swap(m_capacity, rhs.m_capacity);
        std::swap(m_items, rhs.m_items);
        return *this;
    }

    /** Changes the logical size to `new_size`, growing the buffer if needed. */
    void resize(std::size_t new_size) {
        if (new_size > m_capacity) {
            reserve(m_capacity * 2 + 1);
        }
        m_size = new_size;
    }

    /**
     * Ensures the buffer can hold at least `new_capacity` elements without
     * reallocation.  Does nothing if `new_capacity <= m_capacity` or if
     * `new_capacity < m_size` (shrinking below live elements is a no-op).
     */
    void reserve(std::size_t new_capacity) {
        if (new_capacity < m_size) {
            return;
        }
        std::span<Item> view{m_items, m_size};
        gsl::owner<Item *> new_items = new Item[new_capacity];
        std::span<Item> new_items_view{new_items, m_capacity};
        for (std::size_t i{}; i < m_size; ++i) {
            new_items_view[i] = std::move(view[i]);
        }
        m_capacity = new_capacity;
        std::swap(m_items, new_items);
        delete[] new_items;
    }

    // ── Element access ────────────────────────────────────────────────────────

    /** Returns a reference to the element at `index`. No bounds checking. */
    Item &operator[](std::size_t index) { return std::span<Item>{m_items, m_size}[index]; }

    /** Returns a const reference to the element at `index`. No bounds checking.
     */
    const Item &operator[](std::size_t index) const {
        return std::span<Item>{m_items, m_size}[index];
    }

    /** Returns true iff the vector contains no live elements. */
    [[nodiscard]] bool is_empty() const { return m_size == 0; }

    /** Returns the number of live elements. */
    [[nodiscard]] std::size_t size() const { return m_size; }

    /** Returns the number of elements the current buffer can hold before
     * reallocation. */
    [[nodiscard]] std::size_t capacity() const { return m_capacity; }

    /** Appends a copy of `new_item`, growing the buffer if necessary. */
    void push_back(const Item &new_item) {
        if (m_size == m_capacity) {
            reserve(m_capacity * 2 + 1);
        }
        std::span<Item>{m_items, m_size}[m_size++] = new_item;
    }

    /** Appends `new_item` by move, growing the buffer if necessary. */
    void push_back(Item &&new_item) {
        if (m_size == m_capacity) {
            reserve(m_capacity * 2 + 1);
        }
        std::span<Item>{m_items, m_size}[m_size++] = std::move(new_item);
    }

    /** Removes the last element by decrementing the size counter. */
    void pop_back() { m_size--; }

    /** Returns a const reference to the last live element. Undefined if empty. */
    [[nodiscard]] const Item &back() const { return std::span<Item>{m_items, m_size}[m_size - 1]; }

    // ── Iterators ─────────────────────────────────────────────────────────────
    using iterator = Item *;
    using const_iterator = Item *;

    iterator begin() { return &std::span<Item>{m_items, m_size}[0]; }
    [[nodiscard]] const_iterator begin() const { return &std::span<Item>{m_items, m_size}[0]; }

    iterator end() { return &std::span<Item>{m_items, m_size}[size()]; }
    [[nodiscard]] const_iterator end() const { return &std::span<Item>{m_items, m_size}[size()]; }
};

} // namespace dsa

#endif // !VECTOR_H_
