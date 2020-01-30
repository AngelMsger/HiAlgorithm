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
 * 题目 55 的衍生题目。题目 55 的反向遍历方法只能确保可达性，不能确保路径最短。对于这样一个单
 * 向，线性的结构，如果要寻找最短路径，只需每次都寻找最远距离范围，再迭代此过程即可。
 */

#include <iostream>
#include <vector>
#include <chrono>

inline size_t min(int lhs, size_t rhs) {
    return lhs < rhs ? lhs : rhs;
}

using namespace std;

class Solution {
public:
    int jump(vector<int>& nums) {
        const auto total = nums.size();
        for (size_t i = 0; i < total; ++i)
            nums[i] = i + nums[i];
        size_t lo = 0, hi = min(nums[lo], total), steps = 0;
        while (hi < total) {
            size_t farthest = nums[lo];
            while (++lo <= hi)
                if (nums[lo] > farthest)
                    farthest = nums[lo];
            ++lo;
            hi = farthest + 1;
            ++steps;
        }
        return steps;
    }
};

int main() {
    Solution solution;

    vector<int> input_1 {1, 0}, input_2 {1, 1, 1, 1};
    auto start = chrono::high_resolution_clock::now();
    auto output_1 = solution.jump(input_1),
         output_2 = solution.jump(input_2);
    auto end = chrono::high_resolution_clock::now();

    cout << output_1 << ", " << output_2;
    cout << "\nin " << chrono::duration<float, milli>(end - start).count()
         << " ms." << endl;
}