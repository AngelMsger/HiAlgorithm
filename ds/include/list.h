#ifndef HIALGORITHM_LIST_H
#define HIALGORITHM_LIST_H

#include <functional>
#include <initializer_list>
#include "base.h"

namespace angelmsger {
template <typename T>
struct ListNode {
    T elem;
    ListNode<T> *prev, *next;
};

// FIXME: 异常情况下的资源释放
template <typename T>
class List {
   private:
    size_t _size = 0;
    ListNode<T> *_head;
    mutable long _lvi = -1;
    mutable ListNode<T> *_lvn = nullptr;

   protected:
    ListNode<T> *move_to(size_t i) const;
    ListNode<T> *remove_cur(ListNode<T> *lhs);
    void reset_last(const long lvi = -1,
                    const ListNode<T> *lvn = nullptr) noexcept;
    void merge_sort(ListNode<T> *begin, ListNode<T> *end);
    void insertion_sort(ListNode<T> *begin, ListNode<T> *end);
    void merge(ListNode<T> *lhs, ListNode<T> *rhs);

   public:
    explicit List();
    List(std::initializer_list<T> args);
    List(const List<T> &rhs);
    virtual ~List();
    List<T> &operator=(const List<T> &rhs);
    inline size_t size() const noexcept;
    inline bool empty() const noexcept;
    inline const T &get(size_t i) const;
    inline T &get(size_t i);
    inline void put(size_t i, const T &val);
    size_t insert(size_t i, const T &val);
    inline size_t remove(size_t i);
    size_t remove(size_t lo, size_t hi);
    size_t disordered() const noexcept;
    void sort(const bool using_merge = true);
    void sort(size_t lo, size_t hi, const bool using_merge = true);
    inline size_t find(const T &val);
    size_t find(const T &val, size_t lo, size_t hi);
    size_t deduplicated();
    size_t uniquify();  // 针对有序列表
    void traverse(function<void(const T &)> visit) const noexcept;
};

template <typename T>
ListNode<T> *List<T>::move_to(size_t i) const {
    ListNode<T> *cur;
    if (_lvi < 0 || i <= _lvi / 2) {
        // [head -> ...]
        cur = _head->next;
        for (auto j = 0; j < i; ++j) cur = cur->next;
    } else if (i <= _lvi) {
        // [... <- last ...]
        auto steps = _lvi - i;
        cur = _lvn;
        for (auto j = 0; j < steps; ++j) cur = cur->prev;
    } else if (i <= _lvi + (_size - _lvi) / 2) {
        // [... last -> ...]
        auto steps = i - _lvi;
        cur = _lvn;
        for (auto j = 0; j < steps; ++j) cur = cur->next;
    } else {
        // [... <- tail]
        auto steps = _size - i;
        cur = _head;
        for (auto j = 0; j < steps; ++j) cur = cur->prev;
    }
    _lvi = i;
    _lvn = cur;
    return cur;
}

template <typename T>
ListNode<T> *List<T>::remove_cur(ListNode<T> *lhs) {
    auto next = lhs->next;
    lhs->prev->next = next;
    next->prev = lhs->prev;
    delete lhs;
    return next;
}

template <typename T>
void List<T>::reset_last(const long lvi, const ListNode<T> *lvn) noexcept {
    _lvi = lvi;
    _lvn = lvn;
}

template <typename T>
List<T>::List() {
    _head = new ListNode<T>();
    _head->prev = _head->next = _head;
}

template <typename T>
List<T>::List(initializer_list<T> args) {
    _head = new ListNode<T>();
    auto cur = _head;
    for (const auto &arg : args) {
        auto next = new ListNode<T>();
        next->elem = arg;
        next->prev = cur;
        cur->next = next;
        cur = next;
        cur->next = _head;
        _head->prev = cur;
        ++_size;
    }
}

template <typename T>
List<T>::List(const List<T> &rhs) {
    _head = new ListNode<T>();
    auto cur = _head;
    rhs.traverse([this](const T &val) {
        auto next = new ListNode<T>();
        next->elem = val;
        next->prev = cur;
        cur->next = next;
        cur = next;
        cur->next = _head;
        _head->prev = cur;
        ++_size;
    });
}

template <typename T>
List<T>::~List() {
    auto cur = _head->next;
    while (cur != _head) cur = remove_cur(cur);
    delete _head;
}

template <typename T>
List<T> &List<T>::operator=(const List<T> &rhs) {
    if (*this == rhs) return *this;
    List<T> lhs(rhs);
    swap(*this, lhs);
    return *this;
}

template <typename T>
size_t List<T>::size() const noexcept {
    return _size;
}

template <typename T>
bool List<T>::empty() const noexcept {
    return _size == 0;
}

template <typename T>
const T &List<T>::get(size_t i) const {
    return (const_cast<List<T> *>(this))->get(i);
}

template <typename T>
T &List<T>::get(size_t i) {
    assert(0 <= i && i < _size);
    return move_to(i)->elem;
}

template <typename T>
void List<T>::put(size_t i, const T &val) {
    assert(0 <= i && i < _size);
    move_to(i)->elem = val;
}

template <typename T>
size_t List<T>::insert(size_t i, const T &val) {
    assert(0 <= i && i <= _size);
    auto pos = move_to(i);
    auto cur = new ListNode<T>();
    cur->elem = val;
    cur->prev = pos->prev;
    cur->prev->next = cur;
    cur->next = pos;
    pos->prev = cur;
    ++_size;
    return i;
}

template <typename T>
size_t List<T>::remove(size_t i) {
    return this->remove(i, i + 1);
}

template <typename T>
size_t List<T>::remove(size_t lo, size_t hi) {
    assert(0 <= lo && lo < hi && hi <= _size);
    auto steps = hi - lo;
    auto cur = move_to(lo);
    for (auto i = 0; i < steps; ++i) {
        auto next = cur->next;
        cur->prev->next = next;
        next->prev = cur->prev;
        delete cur;
        cur = next;
        --_size;
    }
    reset_last();
    return steps;
}

template <typename T>
size_t List<T>::disordered() const noexcept {
    if (_size < 2) return 0;
    size_t n = 0;
    for (auto cur = _head->next->next; cur != _head; cur = cur->next)
        n += (cur->elem < cur->prev->elem);
    return n;
}

template <typename T>
void List<T>::sort(const bool using_merge) {
    this->sort(0, _size, using_merge);
}

template <typename T>
void List<T>::sort(size_t lo, size_t hi, const bool using_merge) {
    auto begin = move_to(lo), end = move_to(hi);
    if (using_merge) {
        this->merge_sort(begin, end);
    } else {
        this->insertion_sort(begin, end);
    }
}

template <typename T>
size_t List<T>::find(const T &val) {
    return this->find(val, 0, _size);
}

template <typename T>
size_t List<T>::find(const T &val, size_t lo, size_t hi) {
    assert(0 <= lo && lo < hi && hi <= _size);
    auto begin = move_to(lo), end = move_to(hi);
    size_t i = 0;
    ListNode<T> *cur;
    for (cur = begin; cur != end && cur->elem != val; cur = cur->next) ++i;
    if (i != hi) reset_last(i, cur);
    return i;
}

template <typename T>
size_t List<T>::deduplicated() {
    auto i = 0;
    auto modified = 0;
    //        auto cur = _head->next->next;
    //        while (cur != _head) {
    //            this->find(t, 0, i)
    //        }
    //        reset_last();
    return modified;
}

template <typename T>
size_t List<T>::uniquify() {
    for (auto cur = _head->next; cur->next != _head; cur = cur->next)
        while (cur->elem == cur->next->elem) cur = this->remove_cur(cur);
    reset_last();
    return 0;
}

template <typename T>
void List<T>::traverse(function<void(const T &)> visit) const noexcept {
    for (auto cur = _head->next; cur != _head; cur = cur->next)
        visit(cur->elem);
}
}  // namespace angelmsger

#endif  // HIALGORITHM_LIST_H
