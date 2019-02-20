#ifndef HIALGORITHM_BSTREE_H
#define HIALGORITHM_BSTREE_H

#include "base.h"
#include "queue.h"
#include "stack.h"

namespace angelmsger {
template <typename K, typename V>
class BSTreeNode {
   public:
    K key;
    V val;
    BSTreeNode<K, V> *parent, *left, *right;
    size_t height = 0;
    BSTreeNode();
    BSTreeNode(K key, V val, BSTreeNode<K, V> *parent = nullptr,
               BSTreeNode<K, V> *left = nullptr,
               BSTreeNode<K, V> *right = nullptr);
    BSTreeNode(const BSTreeNode<K, V> &) = delete;

    BSTreeNode<K, V> *operator=(const BSTreeNode<K, V> &) = delete;
    inline size_t size() const;
    inline bool is_left() const;
    inline bool is_right() const;
    inline BSTreeNode<K, V> *&insert_as_left(const K &key, const V &val);
    inline BSTreeNode<K, V> *&insert_as_right(const K &key, const V &val);

    virtual BSTreeNode<K, V> *next() const;

    friend void swap(BSTreeNode<K, V> &lhs, BSTreeNode<K, V> &rhs) {
        using std::swap;
        auto lhs_pos = const_cast<BSTreeNode<K, V> *>(&lhs),
             rhs_pos = const_cast<BSTreeNode<K, V> *>(&rhs);
        if (lhs.is_left())
            lhs.parent->left = rhs_pos;
        else if (lhs.is_right())
            lhs.parent->right = rhs_pos;
        if (lhs.left) lhs.left->parent = rhs_pos;
        if (lhs.right) lhs.right->parent = rhs_pos;
        if (rhs.is_left())
            rhs.parent->left = lhs_pos;
        else if (rhs.is_right())
            rhs.parent->right = lhs_pos;
        if (rhs.left) rhs.left->parent = lhs_pos;
        if (rhs.right) rhs.right->parent = lhs_pos;
        swap(lhs.parent, rhs.parent);
        swap(lhs.left, rhs.left);
        swap(lhs.right, rhs.right);
        swap(lhs.height, rhs.height);
    }
};

template <typename K, typename V>
BSTreeNode<K, V>::BSTreeNode()
    : parent(nullptr), left(nullptr), right(nullptr) {}

template <typename K, typename V>
BSTreeNode<K, V>::BSTreeNode(K key, V val, BSTreeNode<K, V> *parent,
                             BSTreeNode<K, V> *left, BSTreeNode<K, V> *right)
    : key(key), val(val), parent(parent), left(left), right(right) {}

template <typename K, typename V>
size_t BSTreeNode<K, V>::size() const {
    return 1 + (left ? left->size() : 0) + (right ? right->size() : 0);
}

template <typename K, typename V>
bool BSTreeNode<K, V>::is_left() const {
    return parent ? parent->left == this : false;
}

template <typename K, typename V>
bool BSTreeNode<K, V>::is_right() const {
    return parent ? parent->right == this : false;
}

template <typename K, typename V>
BSTreeNode<K, V> *&BSTreeNode<K, V>::insert_as_left(const K &key,
                                                    const V &val) {
    return left = new BSTreeNode<K, V>(key, val, this);
}

template <typename K, typename V>
BSTreeNode<K, V> *&BSTreeNode<K, V>::insert_as_right(const K &key,
                                                     const V &val) {
    return right = new BSTreeNode<K, V>(key, val, this);
}

template <typename K, typename V>
BSTreeNode<K, V> *BSTreeNode<K, V>::next() const {
    BSTreeNode<K, V> *cur;
    if ((cur = right))
        while (cur->left) cur = cur->left;
    else if ((cur = parent))
        while (cur->is_right()) cur = cur->parent;
    return cur;
}

template <typename N>
inline long stature(N *pos) {
    return pos ? pos->height : -1;
}

template <typename K, typename V, typename N = BSTreeNode<K, V>>
class BSTree {
   private:
    N *_root = nullptr;
    mutable N *_lvn = nullptr;
    size_t _size = 0;
    void update_height_above(N *pos);
    N *&search_in(const K &key) const;

   protected:
    virtual size_t update_height(N *pos);
    //    virtual N *insert_as_left(N *pos, const K &key, const V &val);
    //    virtual N *insert_as_right(N *pos, const K &key, const V &val);
    virtual N *insert_at(N *&pos, N *lvn, const K &key, const V &val);
    virtual N *remove_at(N *&pos);

   public:
    inline size_t size() const noexcept;
    inline long height() const noexcept;
    inline bool empty() const noexcept;
    inline const V *get(const K &key) const;
    inline V *get(const K &key);
    void set(const K &key, const V &val);
    void remove(const K &key);
    inline void traverse_bfs(function<void(const K &, const V &)> func) const;
    void traverse_bfs(function<void(K &, V &)> func);
    inline void traverse_dfs_prev(
        function<void(const K &, const V &)> func) const;
    void traverse_dfs_prev(function<void(K &, V &)> func);
    inline void traverse_dfs_in(
        function<void(const K &, const V &)> func) const;
    void traverse_dfs_in(function<void(K &, V &)> func);
    inline void traverse_dfs_post(
        function<void(const K &, const V &)> func) const;
    void traverse_dfs_post(function<void(K &, V &)> func);
};

template <typename K, typename V, typename N>
void BSTree<K, V, N>::update_height_above(N *pos) {
    while (pos) {
        auto origin = pos->height;
        auto updated = this->update_height(pos);
        if (origin == updated) break;
        pos = pos->parent;
    }
}

template <typename K, typename V, typename N>
N *&BSTree<K, V, N>::search_in(const K &key) const {
    if (_lvn && _lvn->key == key) return _lvn;
    auto cur = const_cast<N **>(&_root);
    while (*cur && (*cur)->key != key) {
        _lvn = *cur;
        cur = key < (*cur)->key ? const_cast<N **>(&((*cur)->left))
                                : const_cast<N **>(&((*cur)->right));
    }
    return *cur;
}

template <typename K, typename V, typename N>
size_t BSTree<K, V, N>::update_height(N *pos) {
    assert(pos);
    return pos->height = 1 + max(stature(pos->left), stature(pos->right));
}

// template <typename K, typename V, typename N>
// N *BSTree<K, V, N>::insert_as_left(N *pos, const K &key, const V &val) {
//    assert(pos && !pos->left);
//    pos->insert_as_left(key, val);
//    ++_size;
//    this->update_height_above(pos);
//    return pos->left;
//}
//
// template <typename K, typename V, typename N>
// N *BSTree<K, V, N>::insert_as_right(N *pos, const K &key, const V &val) {
//    assert(pos && !pos->right);
//    pos->insert_as_right(key, val);
//    ++_size;
//    this->update_height_above(pos);
//    return pos->right;
//}

template <typename K, typename V, typename N>
N *BSTree<K, V, N>::insert_at(N *&pos, N *lvn, const K &key, const V &val) {
    return pos = new N(key, val, lvn);
}

template <typename K, typename V, typename N>
N *BSTree<K, V, N>::remove_at(N *&pos) {
    if (pos->left && pos->right) {
        auto cur = pos, next = cur->next();
        swap(*cur, *next);
        pos = next;
        auto parent = cur->parent;
        auto &ref = cur->is_left() ? parent->left : parent->right;
        ref = this->remove_at(cur);
        return pos;
    } else {
        N *replace;
        if (!pos->left)
            replace = pos->right;
        else
            replace = pos->left;
        if (replace) replace->parent = pos->parent;
        delete pos;
        return pos = replace;
    }
}

template <typename K, typename V, typename N>
size_t BSTree<K, V, N>::size() const noexcept {
    return _size;
}

template <typename K, typename V, typename N>
long BSTree<K, V, N>::height() const noexcept {
    return stature(_root);
}

template <typename K, typename V, typename N>
bool BSTree<K, V, N>::empty() const noexcept {
    return !_root;
}

template <typename K, typename V, typename N>
const V *BSTree<K, V, N>::get(const K &key) const {
    return const_cast<BSTree<K, V, N> *>(this)->get(key);
}

template <typename K, typename V, typename N>
V *BSTree<K, V, N>::get(const K &key) {
    auto &pos = this->search_in(key);
    return pos ? &(pos->val) : nullptr;
}

template <typename K, typename V, typename N>
void BSTree<K, V, N>::set(const K &key, const V &val) {
    auto &pos = this->search_in(key);
    if (!pos) {
        this->insert_at(pos, _lvn, key, val);
        this->update_height_above(pos);
        ++_size;
    } else
        pos->val = val;
}

template <typename K, typename V, typename N>
void BSTree<K, V, N>::remove(const K &key) {
    auto &pos = this->search_in(key);
    if (!pos) return;
    this->remove_at(pos);
    this->update_height_above(_lvn);
    --_size;
}

template <typename K, typename V, typename N>
void BSTree<K, V, N>::traverse_bfs(
    function<void(const K &, const V &)> func) const {
    const_cast<BSTree<K, V, N> *>(this)->traverse_bfs(func);
}

template <typename K, typename V, typename N>
void BSTree<K, V, N>::traverse_bfs(function<void(K &, V &)> func) {
    if (!_root) return;
    Queue<N *> queue;
    queue.push(_root);
    while (!queue.empty()) {
        auto cur = queue.pop();
        func(cur->key, cur->val);
        if (cur->left) queue.push(cur->left);
        if (cur->right) queue.push(cur->right);
    }
}

template <typename K, typename V, typename N>
void BSTree<K, V, N>::traverse_dfs_prev(
    function<void(const K &, const V &)> func) const {
    const_cast<BSTree<K, V, N> *>(this)->traverse_dfs_prev(func);
}

template <typename K, typename V, typename N>
void BSTree<K, V, N>::traverse_dfs_prev(function<void(K &, V &)> func) {
    if (!_root) return;
    Stack<N *> stack;
    stack.push(_root);
    while (!stack.empty()) {
        for (auto cur = stack.pop(); cur; cur = cur->left) {
            func(cur->key, cur->val);
            if (cur->right) stack.push(cur->right);
        }
    }
}

template <typename K, typename V, typename N>
void BSTree<K, V, N>::traverse_dfs_in(
    function<void(const K &, const V &)> func) const {
    const_cast<BSTree<K, V, N> *>(this)->traverse_dfs_in(func);
}

template <typename K, typename V, typename N>
void BSTree<K, V, N>::traverse_dfs_in(function<void(K &, V &)> func) {
    if (!_root) return;
    Stack<N *> stack;
    auto cur = _root;
    do {
        while (cur) {
            stack.push(cur);
            cur = cur->left;
        }
        cur = stack.pop();
        func(cur->key, cur->val);
        cur = cur->right;
    } while (cur || !stack.empty());
}

template <typename K, typename V, typename N>
void BSTree<K, V, N>::traverse_dfs_post(
    function<void(const K &, const V &)> func) const {
    const_cast<BSTree<K, V, N> *>(this)->traverse_dfs_post(func);
}

template <typename K, typename V, typename N>
void BSTree<K, V, N>::traverse_dfs_post(function<void(K &, V &)> func) {
    if (!_root) return;
    Stack<N *> stack;
    N *last = nullptr;
    auto cur = _root;
    do {
        while (cur) {
            stack.push(cur);
            cur = cur->left;
        }
        cur = stack.top();
        if (!cur->right || last == cur->right) {
            func(cur->key, cur->val);
            last = stack.pop();
            cur = nullptr;
        } else {
            cur = cur->right;
        }
    } while (cur || !stack.empty());
}
}  // namespace angelmsger

#endif  // HIALGORITHM_BSTREE_H
