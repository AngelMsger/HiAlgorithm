/**
 * 256 - 房屋染色
 * 原题目在 LeetCode 上需要订阅才可以访问，未订阅用户可以使用 LintCode。
 * LeetCode: https://leetcode.com/problems/paint-house
 * LintCode: https://www.lintcode.com/problem/paint-house
 *
 * 这里有n个房子在一列直线上，现在我们需要给房屋染色，分别有红色蓝色和绿色。每个房屋染不同的颜色费用也不同，
 * 你需要设计一种染色方案使得相邻的房屋颜色不同，并且费用最小，返回最小的费用。
 * 费用通过一个nx3 的矩阵给出，比如cost[0][0]表示房屋0染红色的费用，cost[1][2]表示房屋1染绿色的费用。
 *
 * 样例 1:
 *
 * 输入: [[14,2,11],[11,14,5],[14,3,10]]
 * 输出: 10
 * 解释: 第一个屋子染蓝色，第二个染绿色，第三个染蓝色，最小花费：2 + 5 + 3 = 10.
 * 样例 2:
 *
 * 输入: [[1,2,3],[1,4,6]]
 * 输出: 3
 *
 * 注意：所有费用都是正整数。
 *
 * 解题思路：
 * 求最值的序列型动态规划。
 * 当讨论前 i 栋房子的时候，最后一栋房子的索引为 i - 1。
 * 最后一步：minCosts[i][j] 表示前 i 栋房子在索引为 i - 1 的房子染成 j 色的条件下的最低成本。
 * 得到子结构：第 i - 1 栋房子有 3 个选择，红，绿和蓝色；当选择红色时，其最低成本为前 i - 1 栋房子在第
 *           i - 2 栋房子染成绿或蓝色的情况下的成本较小者与第 i - 1 栋房子染成红色的成本之和。第
 *           i - 1 栋房子染成绿或蓝色时同理。
 * 得到递推式：minCounts[i][j] = min{ minCounts[i - 1][!= j] } + costs[i - 1][j]
 * 边界条件：minCounst[0] = { 0, 0, 0 }
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
    int minCost(vector<vector<int>> &costs) {
        auto houseCount = costs.size();
        if (houseCount == 0) return 0;
        auto colorCount = costs[0].size();
        int **minCosts = new int *[(houseCount + 1)];
        for (auto i = 0; i <= houseCount; ++i) {
            minCosts[i] = new int[colorCount];
        }

        minCosts[0][0] = minCosts[0][1] = minCosts[0][2] = 0;
        for (auto i = 1; i <= houseCount; ++i) {
            for (auto j = 0; j < colorCount; ++j) {
                auto minCostsWithColorJ = INT_MAX;
                for (auto k = 0; k < colorCount; ++k) {
                    if (j == k) continue;
                    auto costWithColorJ = minCosts[i - 1][k] + costs[i - 1][j];
                    if (costWithColorJ < minCostsWithColorJ)
                        minCostsWithColorJ = costWithColorJ;
                }
                minCosts[i][j] = minCostsWithColorJ;
            }
        }

        auto minCost = INT_MAX;
        for (auto i = 0; i < colorCount; ++i) {
            if (minCosts[houseCount][i] < minCost) {
                minCost = minCosts[houseCount][i];
            }
        }

        for (auto i = 0; i <= houseCount; ++i) {
            delete[] minCosts[i];
        }
        delete[] minCosts;

        return minCost;
    }
};

int main() {
    Solution solution;
    vector<vector<int>> costs /* 10 */ {
            {14, 2,  11},
            {11, 14, 5},
            {14, 3,  10}
    };
    cout << solution.minCost(costs) << endl;
}