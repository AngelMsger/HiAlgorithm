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
    BSTreeNode();
    BSTreeNode(K key, V val, BSTreeNode<K, V> *parent = nullptr,
               BSTreeNode<K, V> *left = nullptr,
               BSTreeNode<K, V> *right = nullptr);
    BSTreeNode(const BSTreeNode<K, V> &) = delete;
    BSTreeNode<K, V> *operator==(const BSTreeNode<K, V> &) = delete;
    BSTreeNode<K, V> *parent, *left, *right;
    size_t height = 0;
    inline size_t size() const;
    BSTreeNode<K, V> *succ() const;
    inline BSTreeNode<K, V> *insert_as_left(const K &key, const V &val);
    inline BSTreeNode<K, V> *insert_as_right(const K &key, const V &val);
    // TODO: Non-Const 副本
    void traverse_bfs(function<void(const K &, const V &)> func) const;
    void traverse_dfs_prev(function<void(const K &, const V &)> func) const;
    void traverse_dfs_in(function<void(const K &, const V &)> func) const;
    void traverse_dfs_post(function<void(const K &, const V &)> func) const;
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
    return 1 + left ? left->size() : 0 + right ? right->size() : 0;
}

template <typename K, typename V>
BSTreeNode<K, V> *BSTreeNode<K, V>::succ() const {
    // FIXME: Wrong Implemention.
    if (!right) return parent;
    auto cur = right;
    while (cur->left) cur = cur->left;
    return cur;
}

template <typename K, typename V>
BSTreeNode<K, V> *BSTreeNode<K, V>::insert_as_left(const K &key, const V &val) {
    return left = new BSTreeNode<K, V>(key, val, this);
}

template <typename K, typename V>
BSTreeNode<K, V> *BSTreeNode<K, V>::insert_as_right(const K &key,
                                                    const V &val) {
    return right = new BSTreeNode<K, V>(key, val, this);
}

template <typename K, typename V>
void BSTreeNode<K, V>::traverse_bfs(
    function<void(const K &, const V &)> func) const {
    Queue<BSTreeNode<K, V> *> queue{this};
    while (!queue.empty()) {
        auto cur = queue.pop();
        func(cur->key, cur->val);
        if (cur->left) queue.push(cur->left);
        if (cur->right) queue.push(cur->right);
    }
}

template <typename K, typename V>
void BSTreeNode<K, V>::traverse_dfs_prev(
    function<void(const K &, const V &)> func) const {
    Stack<BSTreeNode<K, V> *> stack{this};
    while (!stack.empty()) {
        for (auto cur = stack.pop(); cur; cur = cur->left) {
            func(cur->key, cur->val);
            if (cur->right) stack.push(cur->right);
        }
    }
}

template <typename K, typename V>
void BSTreeNode<K, V>::traverse_dfs_in(
    function<void(const K &, const V &)> func) const {
    Stack<BSTreeNode<K, V> *> stack;
    auto cur = this;
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

template <typename K, typename V>
void BSTreeNode<K, V>::traverse_dfs_post(
    function<void(const K &, const V &)> func) const {
    Stack<BSTreeNode<K, V> *> stack;
    BSTreeNode<K, V> *last = nullptr;
    auto cur = this;
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

template <typename N>
inline long stature(N *pos) {
    return pos ? pos->height : -1;
}

template <typename K, typename V, typename N = BSTreeNode<K, V>>
class BSTree {
   private:
    N *_root = nullptr;
    size_t _size = 0;
    void update_height_above(N *pos);

   protected:
    virtual size_t update_height(N *pos);
    virtual N *insert_as_left(const N *pos, const K &key, const V &val);
    virtual N *insert_as_right(const N *pos, const K &key, const V &val);

   public:
    inline size_t size() const noexcept;
    inline bool empty() const noexcept;
    // TODO: Non-Const 副本
    void traverse_bfs(function<void(const K &, const V &)> func) const;
    void traverse_dfs_prev(function<void(const K &, const V &)> func) const;
    void traverse_dfs_in(function<void(const K &, const V &)> func) const;
    void traverse_dfs_post(function<void(const K &, const V &)> func) const;
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
size_t BSTree<K, V, N>::update_height(N *pos) {
    assert(pos);
    return pos->height = 1 + max(stature(pos->left), stature(pos->right));
}

template <typename K, typename V, typename N>
N *BSTree<K, V, N>::insert_as_left(const N *pos, const K &key, const V &val) {
    assert(pos && !pos->left);
    pos->insert_as_left(key, val);
    ++_size;
    this->update_height_above(pos);
    return pos->left;
}

template <typename K, typename V, typename N>
N *BSTree<K, V, N>::insert_as_right(const N *pos, const K &key, const V &val) {
    assert(pos && !pos->right);
    pos->insert_as_right(key, val);
    ++_size;
    this->update_height_above(pos);
    return pos->right;
}

template <typename K, typename V, typename N>
size_t BSTree<K, V, N>::size() const noexcept {
    return _size;
}

template <typename K, typename V, typename N>
bool BSTree<K, V, N>::empty() const noexcept {
    return !_root;
}

template <typename K, typename V, typename N>
void BSTree<K, V, N>::traverse_bfs(
    function<void(const K &, const V &)> func) const {
    if (_root) _root->traverse_bfs(func);
}

template <typename K, typename V, typename N>
void BSTree<K, V, N>::traverse_dfs_prev(
    function<void(const K &, const V &)> func) const {
    if (_root) _root->traverse_dfs_prev(func);
}

template <typename K, typename V, typename N>
void BSTree<K, V, N>::traverse_dfs_in(
    function<void(const K &, const V &)> func) const {
    if (_root) _root->traverse_dfs_in(func);
}

template <typename K, typename V, typename N>
void BSTree<K, V, N>::traverse_dfs_post(
    function<void(const K &, const V &)> func) const {
    if (_root) _root->traverse_dfs_post(func);
}
}  // namespace angelmsger

#endif  // HIALGORITHM_BSTREE_H
