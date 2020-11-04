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
private:
    int robSub(vector<int>& nums) {
        auto houseCount = nums.size();
        if (houseCount == 0) return 0;
        auto *maxRob = new int[houseCount + 1];
        maxRob[0] = 0;
        maxRob[1] = nums[0];
        for (auto i = 2; i <= houseCount; ++i) {
            maxRob[i] = max(maxRob[i - 2] + nums[i - 1], maxRob[i - 1]);
        }
        auto subMax = maxRob[houseCount];
        delete[] maxRob;
        return subMax;
    }
public:
    int rob(vector<int>& nums) {
        if (nums.empty()) return 0;
        if (nums.size() == 1) return nums[0];
        vector<int> withoutFront(nums.cbegin() + 1, nums.cend());
        vector<int> withoutBack(nums.cbegin(), nums.cend() - 1);
        return max(this->robSub(withoutFront), this->robSub(withoutBack));
    }
};

int main() {
    Solution solution;
    vector<int> nums_1 /* 3 */ {2, 3, 2}, nums_2/* 4 */{1, 2, 3, 1};
    cout << solution.rob(nums_1) << '\n'
         << solution.rob(nums_2) << endl;
    return 0;
}
