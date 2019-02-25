#ifndef HIALGORITHM_BSTREE_H
#define HIALGORITHM_BSTREE_H

#include "base.h"
#include "queue.h"
#include "stack.h"

namespace angelmsger {
template <typename K, typename V>
/**
 * 二叉树节点
 */
class BSTreeNode {
   public:
    // 关键码
    K key;
    // 值
    V val;
    // 亲属关系 (父亲, 左孩子, 右孩子)
    BSTreeNode<K, V> *parent, *left, *right;
    // 以当前节点为根的子树规模
    size_t height = 0;
    BSTreeNode();
    BSTreeNode(K key, V val, BSTreeNode<K, V> *parent = nullptr,
               BSTreeNode<K, V> *left = nullptr,
               BSTreeNode<K, V> *right = nullptr);
    BSTreeNode(const BSTreeNode<K, V> &) = delete;
    BSTreeNode<K, V> *operator=(const BSTreeNode<K, V> &) = delete;
};

template <typename K, typename V>
BSTreeNode<K, V>::BSTreeNode()
    : parent(nullptr), left(nullptr), right(nullptr) {}

template <typename K, typename V>
BSTreeNode<K, V>::BSTreeNode(K key, V val, BSTreeNode<K, V> *parent,
                             BSTreeNode<K, V> *left, BSTreeNode<K, V> *right)
    : key(key), val(val), parent(parent), left(left), right(right) {}

// 语义统一化的节点高度
template <typename N>
inline long tree_height(N *pos) {
    return pos ? pos->height : -1;
}

// 以某一节点为根的子树规模
template <typename N>
inline size_t tree_size(const N *pos) {
    if (!pos)
        return 0;
    else
        return 1 + tree_size(pos->left) + tree_size(pos->right);
}

// 是否为父亲的左孩子
template <typename N>
inline bool is_left_child(const N *pos) {
    return pos->parent && pos == pos->parent->left;
}

// 是否为父亲的右孩子
template <typename N>
inline bool is_right_child(const N *pos) {
    return pos->parent && pos == pos->parent->right;
}

// 某一节点中序遍历下的下一节点
template <typename N>
N *next_node(N *pos) {
    auto cur = pos;
    if ((cur = pos->right))
        while (cur->left) cur = cur->left;
    else if ((cur = pos->parent))
        while (is_right_child(cur)) cur = cur->parent;
    return cur;
}

// 更高的孩子
template <typename N>
inline N *taller(const N *pos) noexcept {
    if (!pos) return nullptr;
    auto left_height = tree_height(pos->left),
         right_height = tree_height(pos->right);
    // 相等情况下优先选择与父亲同侧者, 便于简化 AVL 树后续操作
    if (left_height == right_height)
        return is_left_child(pos) ? pos->left : pos->right;
    else
        return (right_height < left_height) ? pos->left : pos->right;
}

// 交换两个节点的亲属关系
template <typename N>
void swap_node(N *lhs, N *rhs) {
    if (is_left_child(lhs))
        lhs->parent->left = rhs;
    else if (is_right_child(lhs))
        lhs->parent->right = rhs;
    if (lhs->left) lhs->left->parent = rhs;
    if (lhs->right) lhs->right->parent = rhs;
    if (is_left_child(rhs))
        rhs->parent->left = lhs;
    else if (is_right_child(rhs))
        rhs->parent->right = lhs;
    if (rhs->left) rhs->left->parent = lhs;
    if (rhs->right) rhs->right->parent = lhs;
    swap(lhs->parent, rhs->parent);
    swap(lhs->left, rhs->left);
    swap(lhs->right, rhs->right);
    swap(lhs->height, rhs->height);
}

/**
 * 二叉搜索树
 */
template <typename K, typename V, typename N = BSTreeNode<K, V>>
class BSTree {
   protected:
    N *_root = nullptr;
    mutable N *_lvn = nullptr;
    size_t _size = 0;
    // 查找
    N *&search_in(const K &key) const;
    // 获取引用
    N *&ref(N *pos);
    // 从指定节点向上更新所有节点的高度
    void update_height_above(N *pos);
    // 更新某一节点的高度
    virtual size_t update_height(N *pos);
    // 在某一位置插入
    virtual N *insert_at(N *&pos, N *lvn, const K &key, const V &val);
    // 在某一位置移除
    virtual N *remove_at(N *&pos);

   public:
    virtual ~BSTree() noexcept;
    // 规模
    inline size_t size() const noexcept;
    // 高度
    inline long height() const noexcept;
    // 是否为空
    inline bool empty() const noexcept;
    // 循关键码取值
    inline const V *get(const K &key) const;
    inline V *get(const K &key);
    // 循关键码赋值
    void set(const K &key, const V &val);
    // 循关键码移除
    void remove(const K &key);
    // 广度优先遍历
    inline void traverse_bfs(function<void(const K &, const V &)> func) const;
    void traverse_bfs(function<void(K &, V &)> func);
    // 前序深度优先遍历
    inline void traverse_dfs_prev(
        function<void(const K &, const V &)> func) const;
    void traverse_dfs_prev(function<void(K &, V &)> func);
    // 中序深度优先遍历
    inline void traverse_dfs_in(
        function<void(const K &, const V &)> func) const;
    void traverse_dfs_in(function<void(K &, V &)> func);
    // 后序深度优先遍历
    inline void traverse_dfs_post(
        function<void(const K &, const V &)> func) const;
    void traverse_dfs_post(function<void(K &, V &)> func);
};

template <typename K, typename V, typename N>
BSTree<K, V, N>::~BSTree() noexcept {
    if (_root) {
        Queue<N *> queue;
        queue.push(_root);
        while (!queue.empty()) {
            auto cur = queue.pop();
            if (cur->left) queue.push(cur->left);
            if (cur->right) queue.push(cur->right);
            delete cur;
        }
        _root = nullptr;
    }
    _size = 0;
    _lvn = nullptr;
}

template <typename K, typename V, typename N>
N *&BSTree<K, V, N>::ref(N *pos) {
    if (pos == _root)
        return _root;
    else if (pos && pos->parent)
        return is_left_child(pos) ? pos->parent->left : pos->parent->right;
    else
        throw "try to get ref of NULL";
}

template <typename K, typename V, typename N>
N *&BSTree<K, V, N>::search_in(const K &key) const {
    if (_lvn && _lvn->key == key)
        return _lvn;
    else
        _lvn = nullptr;
    auto cur = const_cast<N **>(&_root);
    while (*cur && (*cur)->key != key) {
        _lvn = *cur;
        cur = key < (*cur)->key ? const_cast<N **>(&((*cur)->left))
                                : const_cast<N **>(&((*cur)->right));
    }
    return *cur;
}

template <typename K, typename V, typename N>
void BSTree<K, V, N>::update_height_above(N *pos) {
    while (pos) {
        this->update_height(pos);
        pos = pos->parent;
    }
}

template <typename K, typename V, typename N>
size_t BSTree<K, V, N>::update_height(N *pos) {
    assert(pos);
    return pos->height =
               1 + max(tree_height(pos->left), tree_height(pos->right));
}

template <typename K, typename V, typename N>
N *BSTree<K, V, N>::insert_at(N *&pos, N *lvn, const K &key, const V &val) {
    pos = new N(key, val, lvn);
    this->update_height_above(pos);
    return pos;
}

template <typename K, typename V, typename N>
N *BSTree<K, V, N>::remove_at(N *&pos) {
    if (pos->left && pos->right) {
        auto cur = pos, next = next_node(cur);
        swap_node(cur, next);
        pos = next;
        auto parent = cur->parent;
        auto &ref = this->ref(cur);
        return ref = this->remove_at(cur);
    } else {
        N *replace;
        if (!pos->left)
            replace = pos->right;
        else
            replace = pos->left;
        if (replace) replace->parent = pos->parent;
        this->update_height_above(replace);
        delete pos;
        return pos = replace;
    }
}

template <typename K, typename V, typename N>
size_t BSTree<K, V, N>::size() const noexcept {
    return _size;
}

template <typename K, typename V, typename N>
long BSTree<K, V, N>::height() const noexcept {
    return tree_height(_root);
}

template <typename K, typename V, typename N>
bool BSTree<K, V, N>::empty() const noexcept {
    return !_root;
}

template <typename K, typename V, typename N>
const V *BSTree<K, V, N>::get(const K &key) const {
    return const_cast<BSTree<K, V, N> *>(this)->get(key);
}

template <typename K, typename V, typename N>
V *BSTree<K, V, N>::get(const K &key) {
    auto &pos = this->search_in(key);
    return pos ? &(pos->val) : nullptr;
}

template <typename K, typename V, typename N>
void BSTree<K, V, N>::set(const K &key, const V &val) {
    auto &pos = this->search_in(key);
    if (!pos) {
        this->insert_at(pos, _lvn, key, val);
        ++_size;
    } else
        pos->val = val;
}

template <typename K, typename V, typename N>
void BSTree<K, V, N>::remove(const K &key) {
    auto &pos = this->search_in(key);
    if (!pos) return;
    this->remove_at(pos);
    --_size;
}

template <typename K, typename V, typename N>
void BSTree<K, V, N>::traverse_bfs(
    function<void(const K &, const V &)> func) const {
    const_cast<BSTree<K, V, N> *>(this)->traverse_bfs(func);
}

template <typename K, typename V, typename N>
void BSTree<K, V, N>::traverse_bfs(function<void(K &, V &)> func) {
    if (!_root) return;
    Queue<N *> queue;
    queue.push(_root);
    while (!queue.empty()) {
        auto cur = queue.pop();
        if (cur->left) queue.push(cur->left);
        if (cur->right) queue.push(cur->right);
        func(cur->key, cur->val);
    }
}

template <typename K, typename V, typename N>
void BSTree<K, V, N>::traverse_dfs_prev(
    function<void(const K &, const V &)> func) const {
    const_cast<BSTree<K, V, N> *>(this)->traverse_dfs_prev(func);
}

template <typename K, typename V, typename N>
void BSTree<K, V, N>::traverse_dfs_prev(function<void(K &, V &)> func) {
    if (!_root) return;
    Stack<N *> stack;
    stack.push(_root);
    while (!stack.empty()) {
        for (auto cur = stack.pop(); cur; cur = cur->left) {
            func(cur->key, cur->val);
            if (cur->right) stack.push(cur->right);
        }
    }
}

template <typename K, typename V, typename N>
void BSTree<K, V, N>::traverse_dfs_in(
    function<void(const K &, const V &)> func) const {
    const_cast<BSTree<K, V, N> *>(this)->traverse_dfs_in(func);
}

template <typename K, typename V, typename N>
void BSTree<K, V, N>::traverse_dfs_in(function<void(K &, V &)> func) {
    if (!_root) return;
    Stack<N *> stack;
    auto cur = _root;
    do {
        while (cur) {
            stack.push(cur);
            cur = cur->left;
        }
        cur = stack.pop();
        func(cur->key, cur->val);
        cur = cur->right;
    } while (cur || !stack.empty());
}

template <typename K, typename V, typename N>
void BSTree<K, V, N>::traverse_dfs_post(
    function<void(const K &, const V &)> func) const {
    const_cast<BSTree<K, V, N> *>(this)->traverse_dfs_post(func);
}

template <typename K, typename V, typename N>
void BSTree<K, V, N>::traverse_dfs_post(function<void(K &, V &)> func) {
    if (!_root) return;
    Stack<N *> stack;
    N *last = nullptr;
    auto cur = _root;
    do {
        while (cur) {
            stack.push(cur);
            cur = cur->left;
        }
        cur = stack.top();
        if (!cur->right || last == cur->right) {
            func(cur->key, cur->val);
            last = stack.pop();
            cur = nullptr;
        } else {
            cur = cur->right;
        }
    } while (cur || !stack.empty());
}
}  // namespace angelmsger

#endif  // HIALGORITHM_BSTREE_H
