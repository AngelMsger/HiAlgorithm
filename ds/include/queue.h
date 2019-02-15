#ifndef HIALGORITHM_QUEUE_H
#define HIALGORITHM_QUEUE_H

#include "list.h"

namespace angelmsger {
template <typename T>
class Queue {
   private:
    List<T> _elems;

   public:
    inline size_t size() const noexcept;
    inline bool empty() const noexcept;
    inline void push(const T &val);
    inline const T &front() const;
    inline T &front();
    inline const T &back() const;
    inline T &back();
    inline T &pop();
};

template <typename T>
size_t Queue<T>::size() const noexcept {
    return _elems.size();
}

template <typename T>
bool Queue<T>::empty() const noexcept {
    return _elems.empty();
}

template <typename T>
void Queue<T>::push(const T &val) {
    _elems.insert(_elems.size(), val);
}

template <typename T>
const T &Queue<T>::front() const {
    return const_cast<Queue<T> *>(this)->front();
}

template <typename T>
T &Queue<T>::front() {
    return _elems.get(0);
}

template <typename T>
const T &Queue<T>::back() const {
    return const_cast<Queue<T> *>(this)->back();
}

template <typename T>
T &Queue<T>::back() {
    return _elems.get(_elems.size() - 1);
}

template <typename T>
T &Queue<T>::pop() {
    T front = move(this->front());
    _elems.erase(0, 1);
    return front;
}
}  // namespace angelmsger

#endif  // HIALGORITHM_QUEUE_H
