#ifndef HIALGORITHM_AVLTREE_H
#define HIALGORITHM_AVLTREE_H

#include "base.h"
#include "bs_tree.h"

namespace angelmsger {

template <typename K, typename V, typename N = BSTreeNode<K, V>>
class AVLTree : public BSTree<K, V, N> {
   protected:
    // 平衡因子
    inline static long balance_factor(N *pos) noexcept;
    // 是否平衡
    inline static bool balanced(N *pos) noexcept;
    // 树的重平衡
    N *rotate_at(N *pos);
    // 3-4 重构
    N *connect_3_4(N *node_1, N *node_2, N *node_3, N *tree_1, N *tree_2,
                   N *tree_3, N *tree_4);
    N *insert_at(N *&pos, N *lvn, const K &key, const V &val) override;
    N *remove_at(N *&pos) override;
};

template <typename K, typename V, typename N>
long AVLTree<K, V, N>::balance_factor(N *pos) noexcept {
    if (!pos)
        return 0;
    else
        return tree_height(pos->left) - tree_height(pos->right);
};

template <typename K, typename V, typename N>
bool AVLTree<K, V, N>::balanced(N *pos) noexcept {
    auto factor = AVLTree<K, V, N>::balance_factor(pos);
    return -1 <= factor && factor <= 1;
}

template <typename K, typename V, typename N>
N *AVLTree<K, V, N>::rotate_at(N *pos) {
    auto parent = pos->parent, grand = parent->parent;
    if (is_left_child(parent)) {
        if (is_left_child(pos)) {
            parent->parent = grand->parent;
            return this->connect_3_4(pos, parent, grand, pos->left, pos->right,
                                     parent->right, grand->right);
        } else {
            pos->parent = grand->parent;
            return this->connect_3_4(parent, pos, grand, parent->left,
                                     pos->left, pos->right, grand->right);
        }
    } else {
        if (is_left_child(pos)) {
            pos->parent = grand->parent;
            return this->connect_3_4(grand, pos, parent, grand->left, pos->left, pos->right, parent->right);
        } else {
            parent->parent = grand->parent;
            return this->connect_3_4(grand, parent, pos, grand->left, parent->left, pos->left, pos->right);
        }
    }
}

template <typename K, typename V, typename N>
N *AVLTree<K, V, N>:: connect_3_4(N *node_1, N *node_2, N *node_3, N *tree_1,
                                 N *tree_2, N *tree_3, N *tree_4) {
    node_1->parent = node_3->parent = node_2;
    node_2->left = node_1;
    node_2->right = node_3;
    node_1->left = tree_1;
    if (tree_1) tree_1->parent = node_1;
    node_1->right = tree_2;
    if (tree_2) tree_2->parent = node_1;
    this->update_height(node_1);
    node_3->left = tree_3;
    if (tree_3) tree_3->parent = node_3;
    node_3->right = tree_4;
    if (tree_4) tree_4->parent = node_3;
    this->update_height(node_3);
    this->update_height(node_2);
    return node_2;
}

template <typename K, typename V, typename N>
N *AVLTree<K, V, N>::insert_at(N *&pos, N *lvn, const K &key, const V &val) {
    auto inserted = BSTree<K, V, N>::insert_at(pos, lvn, key, val);
    for (auto cur = inserted->parent; cur; cur = cur->parent) {
        if (AVLTree<K, V, N>::balanced(cur))
            this->update_height(cur);
        else {
            auto &ref = this->ref(cur);
            ref = this->rotate_at(taller(taller(cur)));
            break;
        }
    }
    return inserted;
}

template <typename K, typename V, typename N>
N *AVLTree<K, V, N>::remove_at(N *&pos) {
    auto replace = BSTree<K, V, N>::remove_at(pos);
    for (auto cur = this->_lvn; cur; cur = cur->parent) {
        if (AVLTree<K, V, N>::balanced(cur))
            this->update_height(cur);
        else {
            auto &ref = this->ref(cur);
            ref = this->rotate_at(taller(taller(cur)));
        }
    }
    return replace;
}
}  // namespace angelmsger

#endif  // HIALGORITHM_AVLTREE_H
