#include <bits/stdc++.h>
using namespace std;

namespace angelmsger {
    template <typename T>
    class TreeNode {
        T val;
        TreeNode *parents = nullptr;
        TreeNode *leftChild = nullptr;
        TreeNode *rightChild = nullptr;
        explicit TreeNode(const T &val) : val(val) {}
    };

    template <typename T>
    class BST {
    private:
        static TreeNode<T> ** searchNext(TreeNode<T> *node, const T &val) {
            assert(node);
            return &(val < node->val ? node->leftChild : node->rightChild);
        }
        static TreeNode<T> * traverseNext(TreeNode<T> *node) {
            assert(node);
            auto cur = node->rightChild;
            while (cur && cur->leftChild) cur = cur->leftChild;
            return cur;
        }
        TreeNode<T> *root;
    public:
        BST() = default;
        // TODO: Implement Copy & Assign Functions.
        BST(const BST &) = delete;
        BST & operator=(const BST &) = delete;
        virtual ~BST() {};
        TreeNode<T> *  search(const T & val) {
            auto cur = root;
            while (cur && cur->val != val) cur = *BST::searchNext(cur, val);
            return cur;
        }
        void insert(const T &val) {
            if (!root) {
                root = new TreeNode(val);
                return;
            }
            auto cur = BST::searchNext(root, val);
            auto prev = root;
            while (*cur) {
                prev = *cur;
                cur = next(*cur, val);
            }
            *cur = new TreeNode<T>(val);
            (*cur)->parents = prev;
        };
        void remove(const T &val) {

        };
        int height() const {};
        void preOrder(function<void (T &)> func) {};
        void inOrder(function<void (T &)> func) {};
        void postOrder(function<void (T &)> func) {};
    };

    // TODO: Implement AVLTree.
    template <typename T>
    class AVLTree : public BST<T> {

    };

    // TODO: Implement RBTree.
    template <typename T>
    class RBTree {

    };
}

// TODO: Implement Test Cases.
int main(int argc, char *argv[]) {
    using namespace angelmsger;
    return 0;
}