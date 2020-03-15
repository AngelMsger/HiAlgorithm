/**
 * 562 - 背包问题 IV
 *
 * 给出 n 个物品, 以及一个数组, nums[i]代表第i个物品的大小,
 * 保证大小均为正数并且没有重复, 正整数 target 表示背包的大小,
 * 找到能填满背包的方案数。
 * 每一个物品可以使用无数次
 *
 * Example
 * 样例1
 * 输入: nums = [2,3,6,7] 和 target = 7
 * 输出: 2
 * 解释:
 * 方案有:
 * [7]
 * [2, 2, 3]
 *
 * 样例2
 * 输入: nums = [2,3,4,5] 和 target = 7
 * 输出: 3
 * 解释:
 * 方案有:
 * [2, 5]
 * [3, 4]
 * [2, 2, 3]
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
     * @param nums: an integer array and all positive numbers, no duplicates
     * @param target: An integer
     * @return: An integer
     */
    int backPackVI(vector<int> &nums, int target) {
        if (target == 0) return 0;
        auto numsCount = nums.size();
        if (numsCount == 0) return 0;
        // i for item count, j for capacity
        auto **solutionForSizeJWithIItem = new int*[numsCount + 1];
        for (auto i = 0; i <= numsCount; ++i) {
            solutionForSizeJWithIItem[i] = new int[target + 1];
            solutionForSizeJWithIItem[i][0] = 1;
        }
        memset(solutionForSizeJWithIItem[0], 0, (target + 1) * sizeof(int));
        for (auto i = 1; i <= numsCount; ++i) {
            auto sizeOfItem = nums[i - 1];
            for (auto j = 1; j <= target; ++j) {
                solutionForSizeJWithIItem[i][j] = solutionForSizeJWithIItem[i - 1][j];
                if (sizeOfItem <= j) {
                    solutionForSizeJWithIItem[i][j] += solutionForSizeJWithIItem[i][j - sizeOfItem];
                } else {
                    solutionForSizeJWithIItem[i][j] += 0;
                }
            }
        }
        auto solution = solutionForSizeJWithIItem[numsCount][target];
        for (auto i = 0; i <= numsCount; ++i) {
            delete[] solutionForSizeJWithIItem[i];
        }
        delete[] solutionForSizeJWithIItem;
        return solution;
    }
};

int main() {
    Solution solution;
    vector<int> size_1{2, 3, 6, 7},
            size_2{2, 3, 4, 5};
    auto target_1 = 7,
            target_2 = 7;
    cout
            << solution.backPackVI(size_1, target_1) /* 2 */ << '\n'
            << solution.backPackVI(size_2, target_2) /* 3 */ << endl;
    return 0;
}
