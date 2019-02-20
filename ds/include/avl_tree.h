#ifndef HIALGORITHM_AVLTREE_H
#define HIALGORITHM_AVLTREE_H

#include "base.h"
#include "bs_tree.h"

namespace angelmsger {
template <typename K, typename V>
class AVLTreeNode : public BSTreeNode<K, V> {
   public:
    K key;
    V val;
    AVLTreeNode<K, V> *parent, *left, *right;
    AVLTreeNode();
    AVLTreeNode(K key, V val, AVLTreeNode<K, V> *parent = nullptr,
                AVLTreeNode<K, V> *left = nullptr,
                AVLTreeNode<K, V> *right = nullptr);
    AVLTreeNode(const AVLTreeNode<K, V> &node) = delete;
    AVLTreeNode<K, V> *operator=(const AVLTreeNode<K, V> &node) = delete;
    AVLTreeNode<K, V> *next() const override;
    inline long balance_factor() const noexcept;
    friend void swap(AVLTreeNode<K, V> &lhs, AVLTreeNode<K, V> &rhs) {
        using std::swap;
        auto lhs_pos = const_cast<AVLTreeNode<K, V> *>(&lhs),
             rhs_pos = const_cast<AVLTreeNode<K, V> *>(&rhs);
        if (lhs.is_left())
            lhs.parent->left = rhs_pos;
        else if (lhs.is_right())
            lhs.parent->right = rhs_pos;
        if (lhs.left) lhs.left->parent = rhs_pos;
        if (lhs.right) lhs.right->parent = rhs_pos;
        if (rhs.is_left())
            rhs.parent->left = lhs_pos;
        else if (rhs.is_right())
            rhs.parent->right = lhs_pos;
        if (rhs.left) rhs.left->parent = lhs_pos;
        if (rhs.right) rhs.right->parent = lhs_pos;
        swap(lhs.parent, rhs.parent);
        swap(lhs.left, rhs.left);
        swap(lhs.right, rhs.right);
        swap(lhs.height, rhs.height);
    }
};

template <typename K, typename V>
long AVLTreeNode<K, V>::balance_factor() const noexcept {
    return stature(left) - stature(right);
}

template <typename K, typename V>
AVLTreeNode<K, V>::AVLTreeNode() : BSTreeNode<K, V>() {}

template <typename K, typename V>
AVLTreeNode<K, V>::AVLTreeNode(K key, V val, AVLTreeNode<K, V> *parent,
                               AVLTreeNode<K, V> *left,
                               AVLTreeNode<K, V> *right)
    : BSTreeNode<K, V>(key, val, parent, left, right) {}

template <typename K, typename V>
AVLTreeNode<K, V> *AVLTreeNode<K, V>::next() const {
    return dynamic_cast<AVLTreeNode<K, V> *>(BSTreeNode<K, V>::next());
}

template <typename K, typename V, typename N = AVLTreeNode<K, V>>
class AVLTree : public BSTree<K, V, N> {
   protected:
    N *&insert_at(N *&pos, N *lvn, const K &key, const V &val) override {
        return dynamic_cast<N *>(
            BSTree<K, V, N>::insert_at(pos, lvn, key, val));
    }

    N *&remove_at(N *&pos) override {
        return dynamic_cast<N *>(BSTree<K, V, N>::remove_at(pos));
    }
};
}  // namespace angelmsger

#endif  // HIALGORITHM_AVLTREE_H
