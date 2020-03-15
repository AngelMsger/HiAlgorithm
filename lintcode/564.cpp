/**
 * 564 - 背包问题 IV
 *
 * 给出一个都是正整数的数组 nums，其中没有重复的数。从中找出所有的
 * 和为 target 的组合个数。
 *
 * Example
 *
 * 样例1
 * 输入: nums = [1, 2, 4] 和 target = 4
 * 输出: 6
 * 解释:
 * 可能的所有组合有：
 * [1, 1, 1, 1]
 * [1, 1, 2]
 * [1, 2, 1]
 * [2, 1, 1]
 * [2, 2]
 * [4]
 *
 * 样例2
 * 输入: nums = [1, 2] 和 target = 4
 * 输出: 5
 * 解释:
 * 可能的所有组合有：
 * [1, 1, 1, 1]
 * [1, 1, 2]
 * [1, 2, 1]
 * [2, 1, 1]
 * [2, 2]
 *
 * Notice
 * 一个数可以在组合中出现多次。
 * 数的顺序不同则会被认为是不同的组合。
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
    int backPackIV(vector<int> &nums, int target) {
        auto numsCount = nums.size();
        auto *solutionForSize = new int[target + 1];
        solutionForSize[0] = 1;
        for (auto i = 1; i <= target; ++i) {
            solutionForSize[i] = 0;
            for (auto j = 0; j < numsCount; ++j) {
                if (nums[j] <= i) {
                    solutionForSize[i] += solutionForSize[i - nums[j]];
                }
            }
        }
        auto solution = solutionForSize[target];
        delete[] solutionForSize;
        return solution;
    }
};

int main() {
    Solution solution;
    vector<int> size_1{1, 2, 4},
            size_2{1, 2};
    auto target_1 = 4,
            target_2 = 4;
    cout
            << solution.backPackIV(size_1, target_1) /* 6 */ << '\n'
            << solution.backPackIV(size_2, target_2) /* 5 */ << endl;
    return 0;
}