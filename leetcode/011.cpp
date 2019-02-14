/**
 * 011 - 盛最多水的容器
 * @see https://leetcode-cn.com/problems/container-with-most-water/description/
 *
 * 给定 n 个非负整数 a1，a2，...，an，每个数代表坐标中的一个点 (i, ai) 。
 * 在坐标内画 n 条垂直线，垂直线 i 的两个端点分别为 (i, ai) 和 (i, 0)。
 *
 * 说明：你不能倾斜容器，且 n 的值至少为 2。
 *
 * 解题思路:
 * 贪心算法，在宽度由长至短的过程中，容量由较短者决定，在较短边长度不变的情况下，无论如何调整较长边
 * 都无法使容量更大。
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
    int maxArea(vector<int>& height) {
        auto front = height.cbegin(), back = height.cend() - 1;
        auto candidate = 0;
        while (front < back) {
            candidate = max(static_cast<int>(back - front) * min(*front, *back),
                            candidate);
            *front < *back ? front++ : back--;
        }
        return candidate;
    }
};

int main(int argc, char* argv[]) {
    Solution solution;
    vector<int> height{1, 8, 6, 2, 5, 4, 8, 3, 7};

    auto start = chrono::high_resolution_clock::now();
    auto result = solution.maxArea(height);
    auto end = chrono::high_resolution_clock::now();

    cout << result;
    cout << "\nin " << chrono::duration<float, milli>(end - start).count()
         << " ms." << endl;

    return 0;
}
