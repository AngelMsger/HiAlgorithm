#include <bits/stdc++.h>
#define stature(p) ((p) ? (p)->height : -1)
using namespace std;

namespace angelmsger {
template <typename T>
struct BinNode {
    T val;
    size_t height = 0;
    BinNode *parent;
    BinNode *lChild;
    BinNode *rChild;
    explicit BinNode(const T &val, const BinNode *parent = nullptr,
                     const BinNode *lChild = nullptr,
                     const BinNode *rChild = nullptr)
        : val(val), parent(parent), lChild(lChild), rChild(rChild) {}
    BinNode *insertAsLC(const T &val) {
        assert(!this->lChild);
        return this->lChild = new BinNode(val, this);
    }
    BinNode *insertAsRC(const T &val) {
        assert(!this->rChild);
        return this->rChild = new BinNode(val, this);
    }
    size_t size() const noexcept {
        return 1 + this->lChild ? this->lChild->size()
                                : 0 + this->rChild ? this->rChild->size() : 0;
    }
    BinNode *succ() {}
};

template <typename T>
class BinTree {
   protected:
    size_t _size;
    BinNode<T> _root;
    // 更新单节点高度，设为虚方法，由于各种二叉树对高度的定义及更新方法不同
    virtual size_t updateHeight(BinNode<T> *node) {
        return node->height =
                   1 + max(stature(node->lChild), stature(node->rChild));
    }
    // 更新某一节点及其祖先的高度
    void updateHeightAbove(BinNode<T> *node) {
        while (node) {
            auto oriHeight = node->height;
            auto newHeight = this->updateHeight(node);
            if (oriHeight == newHeight) break;
        }
    }
    // 插入为树种某节点的左孩子
    BinNode<T> *insertAsLC(const T &val, const BinNode<T> *node) {
        assert(!node->lChild);
        _size++;
        auto pos = node->insertAsLC(val);
        updateHeightAbove(node);
        return pos;
    }
    // 插入为树种某节点的右孩子
    BinNode<T> *insertAsRC(const T &val, const BinNode<T> *node) {
        assert(!node->rChild);
        _size++;
        auto pos = node->insertAsRC(val);
        updateHeightAbove(node);
        return pos;
    }
    // TODO: 替换为自实现栈
    // 先序遍历
    void travPre(const function<void(const T &)> visit,
                 const BinNode<T> *node) {
        assert(node);
        stack<BinNode<T> *> toVisit;
        toVisit.push(node);
        while (!toVisit.empty()) {
            auto top = move(toVisit.top());
            toVisit.pop();
            visit(top);
            if (top->rChild) toVisit.push(top->rChild);
            if (top->lChild) toVisit.push(top->lChild);
        }
    }
    // 中序遍历
    void travIn(const function<void(const T &)> visit, const BinNode<T> *node) {
        assert(node);
        stack<BinNode<T> *> toVisit;
        toVisit.push(node);
        while (!toVisit.empty()) {
            auto top = move(toVisit.top());
            toVisit.pop();
            while (top->lChild) {
                toVisit.push(top);
                top = top->lChild;
            }
            visit(top);
            if (top->lChild) toVisit.push(top->lChild);
        }
    }
    void travPost(const function<void(const T &)> visit,
                  const BinNode<T> *node) {
        assert(node);
        stack<BinNode<T> *> toVisit;
        toVisit.push(node);
        while (!toVisit.empty()) {
            auto top = move(toVisit.top());
            toVisit.pop();
            while (top->lChild) {
                toVisit.push(top);
                top = top->lChild;
            }
            visit(top);
            toVisit.push(top->rChild);
            toVisit.push(top->lChild);
        }
    }

   public:
    size_t size() const noexcept { return _size; }
    bool empty() const noexcept { return !_root; }
    BinNode<T> root() const noexcept { return _root; }
};

// TODO: Implement AVLTree.
template <typename T>
class AVLTree : public BinTree<T> {};

// TODO: Implement RBTree.
template <typename T>
class RBTree {};
}  // namespace angelmsger

// TODO: Implement Test Cases.
int main(int argc, char *argv[]) {
    using namespace angelmsger;
    return 0;
}
