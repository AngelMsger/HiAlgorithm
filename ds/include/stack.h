#ifndef HIALGORITHM_STACK_H
#define HIALGORITHM_STACK_H

#include "list.h"

namespace angelmsger {
template <typename T>
class Stack {
   private:
    List<T> _elem;

   public:
    inline size_t size() const noexcept;
    inline bool empty() const noexcept;
    inline void push(const T &val);
    inline const T &top() const;
    inline T &top();
    inline T &pop();
};

template <typename T>
size_t Stack<T>::size() const noexcept {
    return _elem.size();
}

template <typename T>
bool Stack<T>::empty() const noexcept {
    return _elem.empty();
}

template <typename T>
void Stack<T>::push(const T &val) {
    _elem.insert(0, val);
}

template <typename T>
const T &Stack<T>::top() const {
    return const_cast<Stack<T> *>(this)->top();
}

template <typename T>
T &Stack<T>::top() {
    return _elem.get(0);
}

template <typename T>
T &Stack<T>::pop() {
    T top = move(this->top());
    _elem.erase(0, 1);
    return top;
}
}  // namespace angelmsger

#endif  // HIALGORITHM_STACK_H
