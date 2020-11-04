/**
 * 265 - 房屋染色 II
 *
 * 原题目在 LeetCode 上为订阅题目，未订阅用户可以使用 LintCode。
 * LintCode: https://www.lintcode.com/problem/paint-house-ii
 * LeetCode: https://leetcode.com/problems/paint-house-ii
 *
 * 这里有n个房子在一列直线上，现在我们需要给房屋染色，共有k种颜色。每个房屋染不同的颜色费用也不同，你需要设
 * 计一种染色方案使得相邻的房屋颜色不同，并且费用最小。
 *
 * 费用通过一个nxk 的矩阵给出，比如cost[0][0]表示房屋0染颜色0的费用，cost[1][2]表示房屋1染颜色2的费用。
 *
 * Example
 * 样例1
 *
 * 输入:
 * costs = [[14,2,11],[11,14,5],[14,3,10]]
 * 输出: 10
 * 说明:
 * 三个屋子分别使用第1,2,1种颜色，总花费是10。
 * 样例2
 *
 * 输入:
 * costs = [[5]]
 * 输出: 5
 * 说明：
 * 只有一种颜色，一个房子，花费为5
 * Challenge
 * 用O(nk)的时间复杂度解决
 *
 * Notice
 * 所有费用都是正整数
 *
 * 解题思路：
 * 此题目与 256 解法基本一致，只是将颜色由 3 种换成了 K 种。由于 K 可能很大，所以需要一点优化策略：
 * 当我们讨论第 i 栋房子的颜色选择时，选择颜色 j 的成本为 min(minCosts[i - 1][!=j]) + costs[i][j]
 * 由于我们需要在位置 i 记录所有的颜色 j，因此会多次计算 min(...)。如果直接使用 256 的解法，最终复杂度为
 * O(NK_2)。
 * 一个技巧是，当我们在数组 [3, 5, 1, 4, 2] 中依次计算除了当前元素以外的最小值时，除了全局最小值 1 以外，
 * 在其他位置求得的结果就是 1，而在 1 处则为全局次小值 2。因此我们只需遍历过程中记录最小值和次小值，即可在
 * 计算 minCosts[i] 时不再需要反复在 minCosts[i - 1] 中遍历。
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
    int minCostII(vector<vector<int>> &costs) {
        auto houseCount = costs.size();
        if (houseCount == 0) return 0;
        auto colorCount = costs[0].size();
        int **minCosts = new int *[(houseCount + 1)];
        for (auto i = 0; i <= houseCount; ++i) {
            minCosts[i] = new int[colorCount];
        }
        for (auto i = 0; i < colorCount; ++i) {
            minCosts[0][i] = 0;
        }

        auto prevColMinCostColor = 0,                   // 上一栋房子最小成本的 j 值
             prevColMinCostColorCost = 0,               // 上一栋房子最小成本
             prevColSecondMinCostColorCost = 0;         // 上一栋房子次小成本
        for (auto i = 1; i <= houseCount; ++i) {
            auto colMinCostColor = 0,                   // 当前房子最小成本的 j 值
                 colMinCostColorCost = INT_MAX,         // 当前房子最小成本
                 colSecondMinCostColorCost = INT_MAX;   // 当前房子次小成本
            for (auto j = 0; j < colorCount; ++j) {
                int cost = costs[i - 1][j];
                if (j == prevColMinCostColor) {
                    cost += prevColSecondMinCostColorCost;
                } else {
                    cost += prevColMinCostColorCost;
                }
                minCosts[i][j] = cost;
                if (cost < colSecondMinCostColorCost) {
                    colSecondMinCostColorCost = cost;
                    if (cost < colMinCostColorCost) {
                        colMinCostColor = j;
                        swap(colSecondMinCostColorCost, colMinCostColorCost);
                    }
                }
            }
            prevColMinCostColor = colMinCostColor;
            prevColMinCostColorCost = colMinCostColorCost;
            prevColSecondMinCostColorCost = colSecondMinCostColorCost;
        }

        auto minCost = minCosts[houseCount][prevColMinCostColor];

        for (auto i = 0; i <= houseCount; ++i) {
            delete[] minCosts[i];
        }
        delete[] minCosts;

        return minCost;
    }
};

int main() {
    Solution solution;
    vector<vector<int>> costs_1 /* 10 */ {
            {14, 2,  11},
            {11, 14, 5},
            {14, 3,  10}
    };
    vector<vector<int>> costs_2 /* 3 */ {
            {1, 2, 3},
            {1, 4, 6}
    };
    cout << solution.minCostII(costs_1) << '\n'
         << solution.minCostII(costs_2) << endl;
}