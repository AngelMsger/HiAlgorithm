/**
 * 018 - 四数之和
 * @see https://leetcode-cn.com/problems/4sum/description/
 *
 * 给定一个包含 n 个整数的数组 nums 和一个目标值 target，判断 nums 中是否存在四个元素
 * a，b，c 和 d ，使得 a + b + c + d 的值与 target 相等？找出所有满足条件且不重复的
 * 四元组。
 *
 * 注意：
 * 答案中不可以包含重复的四元组。
 *
 * 示例：
 * 给定数组 nums = [1, 0, -1, 0, -2, 2]，和 target = 0。
 * 满足要求的四元组集合为：
 * [
 *  [-1,  0, 0, 1],
 *  [-2, -1, 1, 2],
 *  [-2,  0, 0, 2]
 * ]
 *
 * 解题思路:
 * 固定一个元素，则剩余部分是一个“三数之和”问题。固定两个元素，则剩余部分是一个“两数之和”
 * 问题。
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
    vector<vector<int>> fourSum(vector<int> &nums, int target) {
        vector<vector<int>> result;
        if (nums.size() < 4) return move(result);
        sort(nums.begin(), nums.end());
        for (auto i = nums.cbegin(); i < nums.cend() - 3; ++i) {
            if (0 <= target && target < *i) continue;
            if (i > nums.cbegin() && *i == *(i - 1)) continue;
            auto triadTarget = target - *i;
            for (auto j = i + 1; j < nums.cend() - 2; ++j) {
                if (j > i + 1 && *j == *(j - 1)) continue;
                const auto tupleTarget = triadTarget - *j;
                auto k = j + 1, l = nums.cend() - 1;
                while (k < l) {
                    auto sum = *k + *l;
                    if (sum < tupleTarget) k++;
                    else if (sum > tupleTarget) l--;
                    else {
                        vector<int> quad{*i, *j, *k, *l};
                        while (*k == quad[2] && k < l) k++;
                        while (*l == quad[3] && k < l) l--;
                        result.push_back(move(quad));
                    }
                }
            }
        }
        return move(result);
    }
};

int main(int argc, char *argv[]) {
    Solution solution;
    vector<int> nums {1, -2, -5, -4, -3, 3, 3, 5};
    const auto target = -11;

    auto start = chrono::high_resolution_clock::now();
    auto result = solution.fourSum(nums, target);
    auto end = chrono::high_resolution_clock::now();

    ostream_iterator<int> console_iter(cout, ",");
    for_each(result.cbegin(), result.cend(), [&console_iter](const auto ultra) {
        copy(ultra.cbegin(), ultra.cend(), console_iter);
        cout << '\n';
    });
    cout << "\nin " << chrono::duration<float, milli>(end - start).count() << " ms." << endl;

    return 0;
}