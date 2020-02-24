/**
 * 62 - 不同路径
 * 一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为“Start” ）。
 * 机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为“Finish”）。
 * 问总共有多少条不同的路径？
 *
 * 例如，上图是一个7 x 3 的网格。有多少可能的路径？
 *
 * 说明：m 和 n 的值均不超过 100。
 *
 * 示例 1:
 *
 * 输入: m = 3, n = 2
 * 输出: 3
 * 解释:
 * 从左上角开始，总共有 3 条路径可以到达右下角。
 * 1. 向右 -> 向右 -> 向下
 * 2. 向右 -> 向下 -> 向右
 * 3. 向下 -> 向右 -> 向右
 * 示例 2:
 *
 * 输入: m = 7, n = 3
 * 输出: 28
 *
 * 解题思路：
 * 动态规划经典题目，符合计数场景。
 * 最后一步：即到达右下角坐标的路径数。
 * 得到子结构：设 wayCounts[i][j] 为到达该坐标的路径数，由于仅可能从左或上方格子到达，因此
 *           到达该坐标的路径数为到达左侧坐标的路径数与到达上方坐标的路径数之和。
 * 得到递推式：wayCounts[i][j] = wayCounts[i - 1][j] + wayCounts[i][j - 1]。
 * 考虑边界条件：wayCounts[0][0] = 1，当 i = 0 或 j = 0 时，到达该坐标仅可能从左侧坐标
 *            (i = 0)或上方坐标(j = 0)来，因此 wayCounts[i][j] = 1;
 */

#include <iostream>

using namespace std;

static auto _ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    int uniquePaths(int m, int n) {
        int wayCounts[101][101];
        for (auto i = 0; i < m; ++i) {
            for (auto j = 0; j < n; ++j) {
                if (i == 0 || j == 0) {
                    wayCounts[i][j] = 1;
                } else {
                    wayCounts[i][j] = wayCounts[i - 1][j] + wayCounts[i][j - 1];
                }
            }
        }
        return wayCounts[m - 1][n - 1];
    }
};

int main() {
    Solution solution;
    cout << solution.uniquePaths(100, 100);
    return 0;
}