/**
 * 110 - 平衡二叉树
 * @see https://leetcode-cn.com/problems/balanced-binary-tree/description/
 *
 * 给定一个二叉树，判断它是否是高度平衡的二叉树。
 * 本题中，一棵高度平衡二叉树定义为：
 * 一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过1。
 *
 * 示例 1:
 * 给定二叉树 [3,9,20,null,null,15,7]
 *     3
 *    / \
 *   9  20
 *     /  \
 *    15   7
 * 返回 true 。
 *
 * 示例 2:
 * 给定二叉树 [1,2,2,3,3,null,null,4,4]
 *        1
 *       / \
 *      2   2
 *     / \
 *    3   3
 *   / \
 *  4   4
 * 返回 false 。
 *
 * 解题思路:
 * 自底向上计算平衡性，避免重复计算。
 */

#include <iostream>
#include <queue>
#include <chrono>

using namespace std;

static auto _ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x);
};

TreeNode::TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

class Solution {
   private:
    const int dfs(const TreeNode *root) {
        if (!root) return 0;
        auto left = dfs(root->left);
        if (left < 0) return -1;
        auto right = dfs(root->right);
        if (right < 0) return -1;
        auto diff = abs(left - right);
        if (1 < diff) return -1;
        return max(left, right) + 1;
    }

   public:
    bool isBalanced(TreeNode *root) { return dfs(root) != -1; }
};

TreeNode *construct(int, TreeNode * = nullptr);
void destruct(TreeNode *);

int main(int argc, char *argv[]) {
    Solution solution;
    auto root = new TreeNode(4);
    for (auto i : {3, 2, 1, 5}) {
        construct(i, root);
    }

    auto start = chrono::high_resolution_clock::now();
    auto result = solution.isBalanced(root);
    auto end = chrono::high_resolution_clock::now();

    cout << result;
    cout << "\nin " << chrono::duration<float, milli>(end - start).count()
         << " ms." << endl;

    destruct(root);
    return 0;
}

// 构造测试树
TreeNode *construct(int val, TreeNode *root) {
    if (!root)
        return new TreeNode(val);
    else {
        auto pN = &(val < root->val ? root->left : root->right);
        return *pN ? construct(val, *pN) : *pN = new TreeNode(val);
    }
}

// 析构测试树
void destruct(TreeNode *root) {
    if (!root) return;
    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty()) {
        const auto cur = q.front();
        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
        q.pop();
        delete cur;
    }
}
