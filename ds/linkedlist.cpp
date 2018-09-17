#include <bits/stdc++.h>
using namespace std;

// TODO: Unfinished.
namespace angelmsger {
    template <typename T>
    struct ListNode {
        T val;
        ListNode *prev;
        ListNode *next;
    };

    template <typename T>
    class LinkedList {
    private:
        ListNode<T> head;
        void cloneDeep(const LinkedList rhs) {

        }
    public:
        LinkedList(const LinkedList &rhs) {
            cloneDeep(rhs);
        }
        LinkedList(const LinkedList<T> &&) noexcept = default;
        void insert(const T &rhs) {}
        void remove(const int i) {}
        void push(const T &rhs) {}
        T pop() {};
        T top() const {};
        void clear() {}
        T & operator[] (const int i) {}
        LinkedList & operator= (const LinkedList<T> rhs) {
            if (rhs != this) {
                cloneDeep(rhs);
            }
            return *this;
        }
        const T & operator[] (const int i) const {}
        size_t size() const noexcept {}
        bool empty() const noexcept {}
        void sort() {}
    };
}

int main() {
    return 0;
}