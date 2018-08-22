/**
 * 001 - 两数之和
 * @see https://leetcode-cn.com/problems/two-sum/description/
 *
 * 给定一个整数数组和一个目标值，找出数组中和为目标值的两个数。
 * 你可以假设每个输入只对应一种答案，且同样的元素不能被重复利用。
 *
 * 示例:
 * 给定 nums = [2, 7, 11, 15], target = 9
 * 因为 nums[0] + nums[1] = 2 + 7 = 9
 * 所以返回 [0, 1]
 *
 * 解题思路:
 * 将已经算过，并且可能会被将来所用的内容选择合适的数据结构缓存下来。
 */

#include <bits/stdc++.h>
using namespace std;

static auto _ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> history;
        for (auto i = 0; i < nums.size(); ++i) {
            auto flag = history.find(target - nums[i]);
            if (flag != history.end()) return {i, flag->second};
            history[nums[i]] = i;
        }
        return {};
    }
};

int main(int argc, char *argv[]) {
    Solution solution;
    vector<int> nums {2, 7, 11, 15};
    int target = 9;

    auto start = chrono::high_resolution_clock::now();
    auto result = solution.twoSum(nums, target);
    auto end = chrono::high_resolution_clock::now();

    auto console_iter = ostream_iterator<int>(cout);
    copy(result.cbegin(), result.cend(), console_iter);
    cout << "\nin " << chrono::duration<float, milli>(end - start).count() << " ms." << endl;

    return 0;
}
