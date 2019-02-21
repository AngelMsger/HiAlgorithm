#ifndef HIALGORITHM_AVLTREE_H
#define HIALGORITHM_AVLTREE_H

#include "base.h"
#include "bs_tree.h"

namespace angelmsger {
template <typename K, typename V, typename N = BSTreeNode<K, V>>
class AVLTree : public BSTree<K, V, N> {
   protected:
    long balance_factor(N *pos) const noexcept;
    N *insert_at(N *&pos, N *lvn, const K &key, const V &val) override;
    N *remove_at(N *&pos) override;
};

template <typename K, typename V, typename N>
long AVLTree<K, V, N>::balance_factor(N *pos) const noexcept {
    if (!pos)
        return 0;
    else
        return tree_height(pos->left) - tree_height(pos->right);
}

template <typename K, typename V, typename N>
N *AVLTree<K, V, N>::insert_at(N *&pos, N *lvn, const K &key, const V &val) {
    return BSTree<K, V, N>::insert_at(pos, lvn, key, val);
}

template <typename K, typename V, typename N>
N *AVLTree<K, V, N>::remove_at(N *&pos) {
    return BSTree<K, V, N>::remove_at(pos);
}
}  // namespace angelmsger

#endif  // HIALGORITHM_AVLTREE_H
