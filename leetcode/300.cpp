/**
 * 300 - 最长上升子序列
 * 给定一个无序的整数数组，找到其中最长上升子序列的长度。
 *
 * 示例:
 *
 * 输入: [10,9,2,5,3,7,101,18]
 * 输出: 4
 * 解释: 最长的上升子序列是 [2,3,7,101]，它的长度是 4。
 * 说明:
 *
 * 可能会有多种最长上升子序列的组合，你只需要输出对应的长度即可。
 * 你算法的时间复杂度应该为 O(n2) 。
 * 进阶: 你能将算法的时间复杂度降低到 O(n log n) 吗?
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
    int lengthOfLIS(vector<int>& nums) {
        auto numCount = nums.size();
        if (numCount == 0) return 0;
        auto globalLongest = 1;
        auto *longest = new int[numCount];
        longest[0] = 1;
        for (auto i = 1; i < numCount; ++i) {
            longest[i] = 1;
            for (auto j = 0; j < i; ++j) {
                if (
                    nums[j] < nums[i] &&        // 与 i 对应元素呈生序关系，即受 i 对应元素影响
                    longest[i] < longest[j] + 1 // 新递增子序列的长度比原本的长
                ) {
                    longest[i] = longest[j] + 1;
                }
            }
            if (globalLongest < longest[i])
                globalLongest = longest[i];
        }

        delete[] longest;
        return globalLongest;
    }
};

int main() {
    Solution solution;
    vector<int> nums_1 /* 4 */ {10, 9, 2, 5, 3, 7, 101, 18},
                nums_2 /* 6 */ {1, 3, 6, 7, 9, 4, 10, 5, 6};
    cout
        << solution.lengthOfLIS(nums_1) << '\n'
        << solution.lengthOfLIS(nums_2) << endl;
    return 0;
}