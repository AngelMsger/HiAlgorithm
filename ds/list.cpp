#include <bits/stdc++.h>
using namespace std;

namespace angelmsger {
template <typename T>
struct ListNode {
    T val;
    ListNode *next;
    ListNode() = default;
    explicit ListNode(T val) : val(val) {}
};

template <typename T>
class LinkedList {
   private:
    ListNode<T> *head = new ListNode<T>;
    ListNode<T> *tail = head;
    size_t length = 0;
    void cloneDeep(const LinkedList &rhs) {
        if (this == &rhs) return;
        clear();
        auto cur = head;
        for (auto s = rhs->head->next; s; s = s->next) {
            cur->next = new ListNode(cur->val);
            tail = cur = cur->next;
            ++length;
        }
    }

   public:
    LinkedList() = default;
    LinkedList(const LinkedList &rhs) { cloneDeep(rhs); }
    LinkedList(LinkedList<T> &&) noexcept = default;
    virtual ~LinkedList() {
        clear();
        delete head;
    }
    void insert(const T &val, const int i) {
        assert(0 <= i && i <= size());
        auto cur = head;
        for (auto j = 0; j < i; ++j) cur = cur->next;
        auto next = cur->next;
        cur->next = new ListNode<T>(val);
        cur->next->next = next;
        if (i == size()) tail = cur->next;
        ++length;
    }
    void remove(const int i) {
        assert(0 <= i && i < size());
        auto cur = head;
        for (auto j = 0; j < i; ++j) cur = cur->next;
        auto next = cur->next ? cur->next->next : nullptr;
        delete cur->next;
        cur->next = next;
        if (i == size() - 1) tail = cur;
        --length;
    }
    void push_back(const T &val) {
        tail->next = new ListNode<T>(val);
        tail = tail->next;
        ++length;
    }
    T &back() { return tail->val; }
    const T &back() const { return tail->val; }
    void clear() {
        auto cur = head->next;
        while (cur) {
            auto next = cur->next;
            delete cur;
            cur = next;
        }
        head->next = nullptr;
        length = 0;
    }
    LinkedList &operator=(const LinkedList<T> rhs) {
        cloneDeep(rhs);
        return *this;
    }
    T &operator[](const int i) {
        assert(0 <= i && i < size());
        auto cur = head;
        for (auto j = 0; j <= i; ++j) cur = cur->next;
        return cur->val;
    }
    const T &operator[](const int i) const {
        return const_cast<LinkedList *>(this)[i];
    }
    size_t size() const noexcept { return length; }
    bool empty() const noexcept { return head == tail; }
    // TODO: Implement Internal Merge Sort.
    void sort() {}
};

template <typename T>
class Stack {
   private:
    LinkedList<T> data;

   public:
    void push(const T &val) { data.push_back(val); }
    T pop() {
        assert(!data.empty());
        T top = data.back();
        data.remove(data.size() - 1);
        return move(top);
    }
    bool empty() const { return data.empty(); }
};

template <typename T>
class Queue {
   private:
    LinkedList<T> data;

   public:
    void push(const T &val) { data.push_back(val); }
    T pop() {
        assert(!data.empty());
        T top = data[0];
        data.remove(0);
        return move(top);
    }
    bool empty() const { return data.empty(); }
};
}  // namespace angelmsger

int main() {
    using namespace angelmsger;
    LinkedList<int> li;
    assert(li.empty());
    li.push_back(1);
    li.push_back(3);
    li.insert(2, 1);
    assert(li.size() == 3);
    assert(li[1] == 2);

    Stack<char> stk;
    stk.push('a');
    stk.push('b');
    assert(stk.pop() == 'b');
    assert(stk.pop() == 'a');

    Queue<double> que;
    que.push(3.14);
    que.push(2.71);
    assert(que.pop() == 3.14);
    assert(que.pop() == 2.71);

    return 0;
}
