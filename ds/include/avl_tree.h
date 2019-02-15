#ifndef HIALGORITHM_AVLTREE_H
#define HIALGORITHM_AVLTREE_H

#include "base.h"
#include "bs_tree.h"

namespace angelmsger {
template <typename K, typename V>
class AVLTreeNode : public BSTreeNode<K, V> {
   public:
    size_t height = 0;
};

template <typename K, typename V, typename N = AVLTreeNode<K, V>>
class AVLTree : public BSTree<K, V, N> {};
}  // namespace angelmsger

#endif  // HIALGORITHM_AVLTREE_H
