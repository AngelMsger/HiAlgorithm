#ifndef HIALGORITHM_PRIORITY_QUEUE_H
#define HIALGORITHM_PRIORITY_QUEUE_H

#include "base.h"

namespace angelmsger {
constexpr size_t DEFAULT_CAPACITY = 8;
constexpr size_t MAX_CAPACITY = 65536;

template <typename T>
class PriorityQueue {
   protected:
    size_t _size;
    size_t _capacity;
    T *_elem;
    virtual void ensure(size_t i);
    // TODO: shrink
    size_t swim(size_t i);  // 上浮
    size_t sink(size_t i);  // 下沉

   public:
    explicit PriorityQueue();
    PriorityQueue(const PriorityQueue<T> &rhs);
    virtual ~PriorityQueue() noexcept;
    PriorityQueue<T> &operator=(const PriorityQueue<T> &rhs);
    void push(const T &t);
    const T &top() const;
    T &top();
    T &pop();
};

template <typename T>
class IndexedPriorityQueue {};

template <typename T>
PriorityQueue<T>::PriorityQueue() : _size(0) {
    _elem = new T[_capacity = DEFAULT_CAPACITY];
}

template <typename T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue<T> &rhs) {
    _elem = new T[_capacity = rhs._capacity];
    _size = rhs._size;
}

template <typename T>
PriorityQueue<T>::~PriorityQueue() noexcept {
    delete[] _elem;
}

template <typename T>
void PriorityQueue<T>::ensure(size_t i) {
    if (i < _capacity)
        return;
    else if (i > MAX_CAPACITY)
        throw "index overflow";
    auto origin = _elem;
    auto capacity = 1;
    while (capacity < i) capacity <<= 1;
    _elem = new T[capacity];
    _capacity = capacity;
    delete[] origin;
}

template <typename T>
size_t PriorityQueue<T>::swim(size_t i) {
    assert(0 <= i && i < _size);
    while (i > 0) {
        auto parent_i = i / 2;
        if (_elem[i] > _elem[parent_i])
            swap(_elem[i], _elem[parent_i]);
        else
            break;
        i = parent_i;
    }
    return i;
}

template <typename T>
size_t PriorityQueue<T>::sink(size_t i) {
    assert(0 <= i && i < _size);
    auto left_child_i = i * 2;
    auto right_child_i = left_child_i + 1;
    while (left_child_i < _size) {
        if (right_child_i == _size) {
            if (_elem[left_child_i] < _elem[i]) {
                swap(_elem[left_child_i], _elem[i]);
                i = left_child_i;
            } else
                break;
        } else {
            if (_elem[left_child_i] < _elem[right_child_i]) {
                if (_elem[left_child_i] < _elem[i]) {
                    swap(_elem[left_child_i] < _elem[i]);
                    i = left_child_i;
                } else
                    break;
            } else {
                if (_elem[right_child_i] < _elem[i]) {
                    swap(_elem[right_child_i], _elem[i]);
                    i = right_child_i;
                } else
                    break;
            }
        }
        left_child_i = i * 2;
        right_child_i = left_child_i + 1;
    }
}

template <typename T>
PriorityQueue<T> &PriorityQueue<T>::operator=(const PriorityQueue<T> &rhs) {
    if (*this == rhs) return *this;
    PriorityQueue<T> lhs(rhs);
    swap(*this, lhs);
    return *this;
}

template <typename T>
void PriorityQueue<T>::push(const T &t) {
    this->ensure(_size);
    _elem[_size] = t;
    this->swim(_size++);
}

template <typename T>
const T &PriorityQueue<T>::top() const {
    return const_cast<PriorityQueue<T> *>(this)->top();
}

template <typename T>
T &PriorityQueue<T>::top() {
    if (_size == 0) throw "index underflow";
    return _elem[0];
}

template <typename T>
T &PriorityQueue<T>::pop() {
    if (_size == 0)
        throw "index underflow";
    else if (_size == 1)
        return _elem[--_size];
    else {
        auto result = _elem[0];
        swap(_elem[0], _elem[--_size]);
        sink(_elem[0]);
        return result;
    }
}
}  // namespace angelmsger

#endif  // HIALGORITHM_PRIORITY_QUEUE_H
