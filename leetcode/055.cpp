/**
 * 055 - 跳跃游戏
 * @see https://leetcode-cn.com/problems/jump-game/submissions/
 *
 * 给定一个非负整数数组，你最初位于数组的第一个位置。
 * 数组中的每个元素代表你在该位置可以跳跃的最大长度。
 * 判断你是否能够到达最后一个位置。
 *
 * 示例 1:
 * 输入: [2,3,1,1,4]
 * 输出: true
 * 解释: 我们可以先跳 1 步，从位置 0 到达 位置 1, 然后再从位置 1 跳 3 步到达最后一个位置。
 *
 * 示例 2:
 * 输入: [3,2,1,0,4]
 * 输出: false
 * 解释: 无论怎样，你总会到达索引为 3 的位置。但该位置的最大跳跃长度是 0 ， 所以你永远不可能
 *      到达最后一个位置。
 *
 * 解题思路:
 * 直观考虑容易想到 DFS 遍历测试可达性，但本体的结构是单向，线性的，如果使用 DFS，会因超时而
 * 不通过。根据上述特征，易想到从重点反向寻找可达点仅需线性时间。
 */

#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

static auto _ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
private:
public:
    bool canJump(vector<int>& nums) {
        if (nums.size() == 1) return true;
        auto start = nums.cbegin(),
             cur   = nums.cend() - 2,
             last  = nums.cend() - 1;
        while (start <= cur) {
            if (cur + *cur >= last) last = cur;
            --cur;
        }
        return last == nums.cbegin();
    }
};

int main() {
    Solution solution;

    vector<int> input_1 {2,3,1,1,4}, input_2 {3,2,1,0,4};
    vector<int> input_3;
    for (auto i = 25000; 0 <= i; --i) input_3.push_back(i);
    input_3.push_back(0);

    auto start = chrono::high_resolution_clock::now();
    auto output_1 = solution.canJump(input_1),
         output_2 = solution.canJump(input_2),
         output_3 = solution.canJump(input_3);
    auto end = chrono::high_resolution_clock::now();

    cout << output_1 << ", " << output_2 << ", " << output_3;
    cout << "\nin " << chrono::duration<float, milli>(end - start).count()
         << " ms." << endl;
}