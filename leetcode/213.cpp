/**
 * 213 - 打家劫舍 II
 * 你是一个专业的小偷，计划偷窃沿街的房屋，每间房内都藏有一定的现金。这个地方所有的房屋都围成一圈，这意味着第一个房屋和最后一个房屋是紧挨着的。同时，相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。
 *
 * 给定一个代表每个房屋存放金额的非负整数数组，计算你在不触动警报装置的情况下，能够偷窃到的最高金额。
 *
 * 示例 1:
 *
 * 输入: [2,3,2]
 * 输出: 3
 * 解释: 你不能先偷窃 1 号房屋（金额 = 2），然后偷窃 3 号房屋（金额 = 2）, 因为他们是相邻的。
 * 示例 2:
 *
 * 输入: [1,2,3,1]
 * 输出: 4
 * 解释: 你可以先偷窃 1 号房屋（金额 = 1），然后偷窃 3 号房屋（金额 = 3）。
 *      偷窃到的最高金额 = 1 + 3 = 4 。
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
    int rob(vector<int>& nums) {
        if (nums.empty()) return 0;
        if (nums.size() == 1) return nums[0];
        if (nums.size() == 2) return max(nums[0], nums[1]);
        if (nums.size() == 3) return max({nums[0], nums[1], nums[2]});
        // 不抢房间 0，房间 n - 1 随意，等效于计算 1 ~ (n - 1)
        vector<int> houseWithoutHead(nums.cbegin() + 1, nums.cend());
        vector<int> maxWithoutHead(nums.size());
        maxWithoutHead[0] = 0;
        maxWithoutHead[1] = houseWithoutHead[0];
        for (auto i = 2; i <= houseWithoutHead.size(); ++i) {
            maxWithoutHead[i] = max(
                maxWithoutHead[i - 1],
                maxWithoutHead[i - 2] + houseWithoutHead[i - 1]
            );
        }
        // 抢房间 0，房间 n - 1 不能抢，等下雨计算 0 + (1 ~ (n - 2))
        vector<int> houseWithHead(nums.cbegin() + 2, nums.cend() - 1);
        vector<int> maxWithHead(nums.size() - 2);
        maxWithHead[0] = 0;
        maxWithHead[1] = houseWithHead[0];
        for (auto i = 2; i <= houseWithHead.size(); ++i) {
            maxWithHead[i] = max(
                maxWithHead[i - 1],
                maxWithHead[i - 2] + houseWithHead[i - 1]
            );
        }
        return max(maxWithoutHead.back(), maxWithHead.back() + nums[0]);
    }
};

int main() {
    Solution solution;
    vector<int> nums_1 /* 3 */ {2, 3, 2}, nums_2/* 4 */{1, 2, 3, 1};
    cout << solution.rob(nums_1) << '\n'
         << solution.rob(nums_2) << endl;
    return 0;
}
