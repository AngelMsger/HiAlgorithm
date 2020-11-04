/**
 * 563 - 背包问题 V
 * 给出 n 个物品, 以及一个数组, nums[i] 代表第i个物品的大小, 保证大小均为正数,
 * 正整数 target 表示背包的大小, 找到能填满背包的方案数。
 * 每一个物品只能使用一次
 *
 * Example
 * 给出候选物品集合 [1,2,3,3,7] 以及 target 7
 *
 * 结果的集合为:
 * [7]
 * [1,3,3]
 * 返回 2
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
    /**
     * @param nums: an integer array and all positive numbers
     * @param target: An integer
     * @return: An integer
     */
    int backPackV(vector<int> &nums, int target) {
        auto numCount = nums.size();
        if (numCount == 0) return 0;
        // 前 i 个数里凑出 j 的方法数
        auto **groupCounts = new int *[numCount + 1];
        for (auto i = 0; i <= numCount; ++i) {
            groupCounts[i] = new int[target + 1];
            // 题意说明只存在整数, 因此必然凑不出 0
            groupCounts[i][0] = 0;
        }
        memset(groupCounts[0], 0x0, (target + 1) * sizeof(int));

        for (auto i = 1; i <= numCount; ++i) {
            auto valueOfI = nums[i - 1];
            for (auto j = 1; j <= target; ++j) {
                int addOn;
                if (valueOfI < j) {
                    addOn = groupCounts[i - 1][j - valueOfI];
                } else if (valueOfI == j) {
                    addOn = 1;
                } else {
                    addOn = 0;
                }
                groupCounts[i][j] = groupCounts[i - 1][j] + addOn;
            }
        }

        auto groupCountForTarget = groupCounts[numCount][target];
        for (auto i = 0; i <= numCount; ++i) {
            delete[] groupCounts[i];
        }
        delete[] groupCounts;
        return groupCountForTarget;
    }
};

int main() {
    Solution solution;
    vector<int> nums{1, 2, 3, 3, 7};
    auto target = 7;
    cout << solution.backPackV(nums, target) << endl;
    return 0;
}