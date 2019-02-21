#ifndef HIALGORITHM_RBTREE_H
#define HIALGORITHM_RBTREE_H

#include "base.h"
#include "bs_tree.h"

namespace angelmsger {
enum Color { red, black };

template <typename K, typename V>
class RBTreeNode {
   public:
    // 关键码
    K key;
    // 值
    V val;
    // 亲属关系 (父亲, 左孩子, 右孩子)
    RBTreeNode<K, V> *parent, *left, *right;
    // 以当前节点为根的子树规模
    size_t height = 0;
    // 节点颜色
    Color color;
    RBTreeNode();
    RBTreeNode(K key, V val, RBTreeNode<K, V> *parent = nullptr,
               RBTreeNode<K, V> *left = nullptr,
               RBTreeNode<K, V> *right = nullptr, Color color = black);
    RBTreeNode(const RBTreeNode<K, V> &node) = delete;
    RBTreeNode<K, V> *operator=(const RBTreeNode<K, V> &node) = delete;
};

template <typename K, typename V>
RBTreeNode<K, V>::RBTreeNode()
    : parent(nullptr), left(nullptr), right(nullptr), color(black) {}

template <typename K, typename V>
RBTreeNode<K, V>::RBTreeNode(K key, V val, RBTreeNode<K, V> *parent,
                             RBTreeNode<K, V> *left, RBTreeNode<K, V> *right,
                             Color color)
    : key(key),
      val(val),
      parent(parent),
      left(left),
      right(right),
      color(color) {}

template <typename K, typename V, typename N = RBTreeNode<K, V>>
class RBTree : public BSTree<K, V, N> {
   protected:
    N *insert_at(N *&pos, N *lvn, const K &key, const V &val) override {
        return BSTree<K, V, N>::insert_at(pos, lvn, key, val);
    }

    N *remove_at(N *&pos) override { return BSTree<K, V, N>::remove_at(pos); }
};
}  // namespace angelmsger

#endif  // HIALGORITHM_RBTREE_H
