#ifndef HIALGORITHM_BSTREE_H
#define HIALGORITHM_BSTREE_H

#include "base.h"

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
    if (!right) return nullptr;
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
    function<void(const K &, const V &)> func) const {}

template <typename K, typename V>
void BSTreeNode<K, V>::traverse_dfs_prev(
    function<void(const K &, const V &)> func) const {}

template <typename K, typename V>
void BSTreeNode<K, V>::traverse_dfs_in(
    function<void(const K &, const V &)> func) const {}

template <typename K, typename V>
void BSTreeNode<K, V>::traverse_dfs_post(
    function<void(const K &, const V &)> func) const {}

template <typename K, typename V, typename N = BSTreeNode<K, V>>
class BSTree {
   private:
    N *_root = nullptr;
    size_t _size = 0;

   protected:
    virtual size_t update_height(N *n);
    virtual void update_height_above(N *n);

   public:
    inline size_t size() const noexcept;
    inline bool empty() const noexcept;
};

template <typename K, typename V, typename N>
size_t BSTree<K, V, N>::update_height(N *n) {
    return 0;
}

template <typename K, typename V, typename N>
void BSTree<K, V, N>::update_height_above(N *n) {}

template <typename K, typename V, typename N>
size_t BSTree<K, V, N>::size() const noexcept {
    return _size;
}

template <typename K, typename V, typename N>
bool BSTree<K, V, N>::empty() const noexcept {
    return !_root;
}
}  // namespace angelmsger

#endif  // HIALGORITHM_BSTREE_H
