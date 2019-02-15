#ifndef HIALGORITHM_VECTOR_H
#define HIALGORITHM_VECTOR_H

#include <functional>
#include <initializer_list>
#include "base.h"

namespace angelmsger {
constexpr size_t DEFAULT_CAPACITY = 8;

template <typename T>
class Vector {
   private:
    size_t _size;
    size_t _capacity;
    T *_elem;

   protected:
    inline virtual void expand();
    // TODO: shrink

   public:
    explicit Vector();
    Vector(std::initializer_list<T> args);
    Vector(const Vector<T> &rhs);
    virtual ~Vector();
    Vector<T> &operator=(const Vector<T> &rhs);
    inline size_t size() const noexcept;
    inline bool empty() const noexcept;
    inline const T &get(size_t i) const noexcept;
    inline T &get(size_t i);
    inline void put(size_t i, const T &val);
    size_t insert(size_t i, const T &val);
    inline size_t erase(size_t i);
    size_t erase(size_t lo, size_t hi);
    size_t remove(const T &val);
    size_t disordered() const noexcept;
    void sort();
    void sort(size_t lo, size_t hi);
    inline size_t find(const T &val);
    size_t find(const T &val, size_t lo, size_t hi);
    inline size_t search(const T &val);  // 针对有序向量
    size_t search(const T &val, size_t lo, size_t hi);
    size_t deduplicated();
    size_t uniquify();  // 针对有序向量
    void traverse(function<void(const T &)> visit) const noexcept;
};

template <typename T>
void Vector<T>::expand() {
    if (_size < _capacity) return;
    _capacity = max(_size, DEFAULT_CAPACITY);
    auto o = _elem;
    _elem = new T[_capacity <<= 1];
    for (auto i = 0; i < _size; ++i) *(_elem + i) = move(*(o + i));
    delete[] o;
}

template <typename T>
Vector<T>::Vector() : _size(0) {
    _elem = new T[_capacity = DEFAULT_CAPACITY];
}

template <typename T>
Vector<T>::Vector(initializer_list<T> args) : _size(0) {
    _capacity = (size_t)pow(2, (size_t)(log2(args.size())) + 1);
    _elem = new T[_capacity];
    auto i = _elem;
    for (auto j = args.begin(); j != args.end(); ++i, ++j) *i = *j;
    _size = i - _elem;
}

template <typename T>
Vector<T>::Vector(const Vector<T> &rhs) {
    _capacity = rhs._capacity;
    _size = rhs._size;
    _elem = new T[_capacity];
    for (auto i = 0; i < _size; ++i) {
        *(_elem + i) = *(rhs._elem + i);
    }
}

template <typename T>
Vector<T>::~Vector() {
    delete[] _elem;
    _elem = nullptr;
    _size = 0;
}

template <typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &rhs) {
    if (*this == rhs) return *this;
    Vector<T> lhs(rhs);
    swap(*this, lhs);
    return *this;
}

template <typename T>
size_t Vector<T>::size() const noexcept {
    return _size;
}

template <typename T>
bool Vector<T>::empty() const noexcept {
    return _size == 0;
}

template <typename T>
const T &Vector<T>::get(size_t i) const noexcept {
    return (const_cast<Vector<T> *>(this))->get(i);
}

template <typename T>
T &Vector<T>::get(size_t i) {
    assert(0 <= i && i < _size);
    return *(_elem + i);
}

template <typename T>
void Vector<T>::put(size_t i, const T &val) {
    assert(0 <= i && i < _size);
    *(_elem + i) = val;
}

template <typename T>
size_t Vector<T>::insert(size_t i, const T &val) {
    assert(0 <= i && i <= _size);
    this->expand();
    for (auto j = _size; i < j; --j) *(_elem + j) = *(_elem + j - 1);
    *(_elem + i) = val;
    ++_size;
    return i;
}

template <typename T>
size_t Vector<T>::erase(size_t i) {
    return this->erase(i, i + 1);
}

template <typename T>
size_t Vector<T>::erase(size_t lo, size_t hi) {
    assert(0 <= lo && lo < hi && hi <= _size);
    while (hi < _size) *(_elem + lo++) = *(_elem + hi++);
    _size = lo;
    return hi - lo;
}

template <typename T>
size_t Vector<T>::remove(const T &val) {
    size_t cur = 0;
    for (auto i = 0; i < _size; ++i) {
        if (*(_elem + i) != val) {
            *(_elem + cur++) = *(_elem + i);
        }
    }
    auto modified = _size - cur;
    _size = cur;
    return modified;
}

template <typename T>
size_t Vector<T>::disordered() const noexcept {
    size_t n = 0;
    for (auto i = 1; i < _size; ++i) n += (*(_elem + i) < *(_elem + i - 1));
    return n;
}

template <typename T>
void Vector<T>::sort() {
    this->sort(0, _size);
}

template <typename T>
void Vector<T>::sort(size_t lo, size_t hi) {
    assert(0 <= lo && hi <= _size);
    auto size = hi - lo;
    if (size < 2) return;
    auto first = _elem + lo, last = _elem + hi;
    auto offset = rand_int(0, size);
    swap(*first, *(first + offset));
    auto i = first + 1;
    for (auto j = i; j < last; ++j) {
        if (*j <= *first) swap(*(i++), *j);
    }
    auto mid = i - 1;
    swap(*first, *mid);
    this->sort(lo, mid - _elem);
    this->sort(mid - _elem, hi);
}

template <typename T>
size_t Vector<T>::find(const T &val) {
    return this->find(val, 0, _size);
}

template <typename T>
size_t Vector<T>::find(const T &val, size_t lo, size_t hi) {
    assert(0 <= lo && lo < hi && hi <= _size);
    while (lo < hi && *(_elem + lo) != val) lo++;
    return lo;
}

template <typename T>
size_t Vector<T>::search(const T &val) {
    return this->search(val, 0, _size);
}

template <typename T>
size_t Vector<T>::search(const T &val, size_t lo, size_t hi) {
    assert(0 <= lo && hi <= _size);
    size_t i = lo, j = hi;
    while (lo < j) {
        i = lo + (j - lo) / 2;
        auto cur = *(_elem + i);
        if (cur < val)
            lo = i;
        else if (val < cur)
            j = i;
        else
            break;
    }
    return *(_elem + i) == val ? i : hi;
}

template <typename T>
size_t Vector<T>::deduplicated() {
    if (_size < 2) return 0;
    size_t i = 1;
    for (auto j = i; j < _size; ++j) {
        auto &t = *(_elem + j);
        if (this->find(t, 0, i) == i) swap(*(_elem + i++), t);
    }
    auto modified = _size - i;
    _size = i;
    return modified;
}

template <typename T>
size_t Vector<T>::uniquify() {
    if (_size < 2) return 0;
    size_t i = 1;
    for (auto j = i; j < _size; ++j) {
        auto &t = *(_elem + j);
        if (*(_elem + i - 1) != *(_elem + j))
            swap(*(_elem + i++), *(_elem + j));
    }
    auto modified = _size - i;
    _size = i;
    return modified;
}

template <typename T>
void Vector<T>::traverse(function<void(const T &)> visit) const noexcept {
    for (auto i = 0; i < _size; ++i) visit(*(_elem + i));
}
}  // namespace angelmsger

#endif  // HIALGORITHM_VECTOR_H
