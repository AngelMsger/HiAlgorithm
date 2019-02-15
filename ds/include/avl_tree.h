#ifndef HIALGORITHM_AVLTREE_H
#define HIALGORITHM_AVLTREE_H

#include "base.h"
#include "bs_tree.h"

namespace angelmsger {
template <typename K, typename V>
struct AVLTreeNode {
    K key;
    V val;
    AVLTreeNode<K, V> *parent = nullptr, *left = nullptr, *right = nullptr;
    size_t height;
};

template <typename K, typename V, typename N = AVLTreeNode<K, V>>
class AVLTree : public BSTree<K, V, N> {};
}  // namespace angelmsger

#endif  // HIALGORITHM_AVLTREE_H
