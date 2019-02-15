#ifndef HIALGORITHM_BSTREE_H
#define HIALGORITHM_BSTREE_H

#include "base.h"

namespace angelmsger {
template <typename K, typename V>
class BSTreeNode {
   public:
    K key;
    V val;
    BSTreeNode<K, V> *parent = nullptr, *left = nullptr, *right = nullptr;
    BSTreeNode<K, V> *succ() const;
};

template <typename K, typename V>
BSTreeNode<K, V> *BSTreeNode<K, V>::succ() const {
    return nullptr;
}

template <typename K, typename V, typename N = BSTreeNode<K, V>>
class BSTree {};
}  // namespace angelmsger

#endif  // HIALGORITHM_BSTREE_H
