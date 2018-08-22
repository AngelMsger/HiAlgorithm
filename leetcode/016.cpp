/**
 * 016 - 最接近的三数之和
 * @see https://leetcode-cn.com/problems/3sum-closest/description/
 *
 * 给定一个包括 n 个整数的数组 nums 和 一个目标值 target。找出 nums 中的三个整数，使得它们的和与 target 最接近。
 * 返回这三个数的和。假定每组输入只存在唯一答案。
 *
 * 例如，给定数组 nums = [-1，2，1，-4], 和 target = 1.与 target 最接近的三个数的和为 2. (-1 + 2 + 1 = 2).
 *
 * 解题思路:
 * 与15题十分类似。
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
    int threeSumClosest(vector<int> &nums, int target) {
        if (nums.size() < 3) return accumulate(nums.cbegin(), nums.cend(), 0);
        sort(nums.begin(), nums.end());
        auto candidate = nums[0] + nums[1] + nums[2], minDiff = abs(candidate - target);
        for (auto i = nums.cbegin(); i < nums.cend() - 2; ++i) {
            if (i > nums.cbegin() && *i == *(i - 1)) continue;
            auto j = i + 1, k = nums.cend() - 1;
            while (j < k) {
                auto sum = *i + *j + *k, diff = abs(sum - target);
                if (diff < minDiff) {
                    candidate = sum;
                    minDiff = diff;
                }
                if (sum < target) ++j;
                else if (sum > target) --k;
                else return candidate;
            }
        }
        return candidate;
    }
};

int main(int argc, char *argv[]) {
    Solution solution;
    vector<int> nums{1, 2, 4, 8, 16, 32, 64, 128};
    auto target = 82;

    auto start = chrono::high_resolution_clock::now();
    auto result = solution.threeSumClosest(nums, target);
    auto end = chrono::high_resolution_clock::now();

    cout << result;
    cout << "\nin " << chrono::duration<float, milli>(end - start).count() << " ms." << endl;

    return 0;
}
