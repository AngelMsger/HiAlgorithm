/**
 * 198 - 打家劫舍
 *
 * 你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻
 * 的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。
 *
 * 给定一个代表每个房屋存放金额的非负整数数组，计算你在不触动警报装置的情况下，能够偷窃到的最高金额。
 *
 * 示例 1:
 *
 * 输入: [1,2,3,1]
 * 输出: 4
 * 解释: 偷窃 1 号房屋 (金额 = 1) ，然后偷窃 3 号房屋 (金额 = 3)。
 *      偷窃到的最高金额 = 1 + 3 = 4 。
 * 示例 2:
 *
 * 输入: [2,7,9,3,1]
 * 输出: 12
 * 解释: 偷窃 1 号房屋 (金额 = 2), 偷窃 3 号房屋 (金额 = 9)，接着偷窃 5 号房屋 (金额 = 1)。
 *      偷窃到的最高金额 = 2 + 9 + 1 = 12 。
 *
 * 解题思路：
 * 序列型动态规划，与 256 - 房屋染色(Paint House) 解法类似。
 * 递推关系：
 * 1. 在抢 i 房间的情况下，累计最大收益是【不抢】i - 1 房间情况下的最大收益 + i 房间的最大收益；
 * 2. 在不抢 i 房间的情况下，累计最大收益是 【抢或不抢】i - 1 房间情况下的最大收益 + i 房间的最大收益。
 * 在 1 中，不抢 i - 1 的最大收益，实际上就是规模为 i - 2 的子问题。
 */

#include <iostream>
#include <vector>

using namespace std;

static auto _ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    int rob(vector<int> &nums) {
        auto houseCount = nums.size();
        if (houseCount == 0) return 0;
        vector<int> maxRobs(houseCount + 1);
        maxRobs[0] = 0;
        maxRobs[1] = nums[0];
        for (auto i = 2; i <= houseCount; ++i) {
            maxRobs[i] = max(maxRobs[i - 2] + nums[i - 1], maxRobs[i - 1]);
        }
        return maxRobs[houseCount];
    }
};

int main() {
    Solution solution;
    vector<int> nums_1 /* 12 */ {2, 7, 9, 3, 1}, nums_2/* 4 */{2, 1, 1, 2};
    cout << solution.rob(nums_1) << '\n'
         << solution.rob(nums_2) << endl;
    return 0;
}