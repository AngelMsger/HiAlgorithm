/**
 * 015 - 三数之和
 * @see https://leetcode-cn.com/problems/3sum/description/
 *
 * 给定一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？
 * 找出所有满足条件且不重复的三元组。
 *
 * 注意：答案中不可以包含重复的三元组。
 * 例如, 给定数组 nums = [-1, 0, 1, 2, -1, -4]，
 * 满足要求的三元组集合为：
 * [
 *  [-1, 0, 1],
 *  [-1, -1, 2]
 * ]
 *
 * 解题思路:
 * 直接遍历带来的问题不仅是时间复杂度的上升，而且难以避免题中不可重复的要求。如果数据有序则问题得以简化。
 *
 * 经验:
 * 当现有解决问题的方案的时间复杂度大于O(nlogn)时才会考虑引入排序以寻求优化。
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
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;
        for (int i = 0; i < nums.size() && nums[i] <= 0; ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            int front = i + 1, back = static_cast<int>(nums.size() - 1), target = -nums[i];
            while (front < back) {
                int sum = nums[front] + nums[back];
                if (sum < target) front++;
                else if (sum > target) back--;
                else {
                    vector<int> triplet {nums[i], nums[front], nums[back]};
                    while(nums[front] == triplet[1] && front < back) front++;
                    while(nums[back] == triplet[2] && front < back) back--;
                    result.push_back(move(triplet));
                }
            }
        }
        return result;
    }
};

int main(int argc, char *argv[]) {
    Solution solution;
    vector<int> nums {-1, 0, 1, 2, -1, -4};

    auto start = chrono::high_resolution_clock::now();
    auto result = solution.threeSum(nums);
    auto end = chrono::high_resolution_clock::now();

    auto console_iter = ostream_iterator<int>(cout, ",");
    for_each(result.cbegin(), result.cend(), [&console_iter](const auto &triple) {
        copy(triple.cbegin(), triple.cend(), console_iter);
        cout << '\n';
    });
    cout << "\nin " << chrono::duration<float, milli>(end - start).count() << " ms." << endl;

    return 0;
}
