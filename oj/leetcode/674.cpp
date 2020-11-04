/**
 * 674 - 最长连续递增序列
 * 给定一个未经排序的整数数组，找到最长且连续的的递增序列。
 *
 * 示例 1:
 *
 * 输入: [1,3,5,4,7]
 * 输出: 3
 * 解释: 最长连续递增序列是 [1,3,5], 长度为3。
 * 尽管 [1,3,5,7] 也是升序的子序列, 但它不是连续的，因为5和7在原数组里被4隔开。
 * 示例 2:
 *
 * 输入: [2,2,2,2,2]
 * 输出: 1
 * 解释: 最长连续递增序列是 [2], 长度为1。
 * 注意：数组长度不会超过10000。
 *
 * 解题思路：
 * 序列型动态规划。
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
    int findLengthOfLCIS(vector<int> &nums) {
        auto numCount = nums.size();
        if (numCount == 0) return 0;
        auto longestIncreasing = 1,
                keepIncreasing = 1;
        for (auto i = 1; i < numCount; ++i) {
            if (nums[i] > nums[i - 1]) {
                ++keepIncreasing;
                if (keepIncreasing > longestIncreasing) {
                    longestIncreasing = keepIncreasing;
                }
            } else {
                keepIncreasing = 1;
            }
        }
        return longestIncreasing;
    }
};

int main() {
    Solution solution;
    vector<int> nums{
            1, 3, 5, 4, 7
    };
    cout << solution.findLengthOfLCIS(nums) << endl;
    return 0;
}
