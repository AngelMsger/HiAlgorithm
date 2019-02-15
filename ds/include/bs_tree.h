#ifndef HIALGORITHM_BSTREE_H
#define HIALGORITHM_BSTREE_H

#include "base.h"

namespace angelmsger {
template <typename K, typename V>
struct TreeNode {
    K key;
    V val;
    TreeNode<K, V> *parent = nullptr, *left = nullptr, *right = nullptr;
};

template <typename K, typename V, typename N = TreeNode<K, V>>
class BSTree {};
}  // namespace angelmsger

#endif  // HIALGORITHM_BSTREE_H
