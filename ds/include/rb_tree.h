#ifndef HIALGORITHM_RBTREE_H
#define HIALGORITHM_RBTREE_H

#include "base.h"
#include "bs_tree.h"

namespace angelmsger {
enum Color { red, black };

template <typename K, typename V>
class RBTreeNode : public BSTreeNode<K, V> {
    size_t height = 0;
    Color color = black;
};

template <typename K, typename V, typename N = RBTreeNode<K, V>>
class RBTree : public BSTree<K, V, N> {};
}  // namespace angelmsger

#endif  // HIALGORITHM_RBTREE_H
