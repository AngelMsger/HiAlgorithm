#ifndef HIALGORITHM_RBTREE_H
#define HIALGORITHM_RBTREE_H

#include "base.h"
#include "bs_tree.h"

namespace angelmsger {
enum Color { red, black };

template <typename K, typename V>
struct RBTreeNode {
    K key;
    V val;
    RBTreeNode<K, V> *parent = nullptr, *left = nullptr, *right = nullptr;
    size_t height = 0;
    Color color = black;
};

template <typename K, typename V, typename N = RBTreeNode<K, V>>
class RBTree : public BSTree<K, V, N> {};
}  // namespace angelmsger

#endif  // HIALGORITHM_RBTREE_H
