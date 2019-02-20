#ifndef HIALGORITHM_RBTREE_H
#define HIALGORITHM_RBTREE_H

#include "base.h"
#include "bs_tree.h"

namespace angelmsger {
enum Color { red, black };

template <typename K, typename V>
class RBTreeNode : public BSTreeNode<K, V> {
public:
    size_t height = 0;
    Color color = black;
    RBTreeNode();
    RBTreeNode(K key, V val, BSTreeNode<K, V> *parent = nullptr, BSTreeNode<K, V> *left = nullptr, BSTreeNode<K, V> *right = nullptr);
    RBTreeNode(const BSTreeNode<K, V> &node) = delete;

    RBTreeNode<K, V> *operator=(const RBTreeNode <K, V> &node) = delete;

    RBTreeNode<K, V> *next() const override {
        return dynamic_cast<RBTreeNode<K, V> *>(BSTreeNode<K, V>::next());
    }

    friend void swap(RBTreeNode<K, V> &lhs, RBTreeNode<K, V> &rhs) {
        using std::swap;
        auto lhs_pos = const_cast<RBTreeNode<K, V> *>(&lhs),
                rhs_pos = const_cast<RBTreeNode<K, V> *>(&rhs);
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

    template<typename K, typename V>
    RBTreeNode<K, V>::RBTreeNode() {

    }

    template<typename K, typename V>
    RBTreeNode<K, V>::RBTreeNode(K key, V val, BSTreeNode<K, V> *parent, BSTreeNode<K, V> *left,
                                 BSTreeNode<K, V> *right):BSTreeNode<K, V>(key, val, parent, left, right) {

    }

    template <typename K, typename V, typename N = RBTreeNode<K, V>>
class RBTree : public BSTree<K, V, N> {
protected:
    N *insert_at(N *&pos, N *lvn, const K &key, const V &val) override {
        return dynamic_cast<N *>(BSTree<K, V>::insert_at(pos, lvn, key, val));
    }

    N *remove_at(N *&pos) override {
        return dynamic_cast<N *>(BSTree<K, V>::remove_at(pos));
    }
};
}  // namespace angelmsger

#endif  // HIALGORITHM_RBTREE_H
