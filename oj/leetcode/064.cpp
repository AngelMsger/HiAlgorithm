/**
 * 064 - 最小路径和
 * 给定一个包含非负整数的 m x n 网格，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。
 * 说明：每次只能向下或者向右移动一步。
 *
 * 示例:
 *
 * 输入:
 * [
 *   [1,3,1],
 *   [1,5,1],
 *   [4,2,1]
 * ]
 * 输出: 7
 * 解释: 因为路径 1→3→1→1→1 的总和最小。
 * 解题思路:
 *
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

static auto _ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    int minPathSum(vector<vector<int>> &grid) {
        auto rowCount = grid.size();
        if (rowCount == 0) return 0;
        auto colCount = grid[0].size();
        if (colCount == 0) return 0;
        // TODO: 可使用滚动数组优化空间复杂度
        int **minCosts = new int *[rowCount];
        for (auto i = 0; i < rowCount; ++i) {
            minCosts[i] = new int[colCount];
        }
        for (auto i = 0; i < rowCount; ++i) {
            for (auto j = 0; j < colCount; ++j) {
                if (i == 0 && j == 0) {
                    minCosts[i][j] = grid[i][j];
                } else if (i == 0) {
                    minCosts[i][j] = minCosts[i][j - 1] + grid[i][j];
                } else if (j == 0) {
                    minCosts[i][j] = minCosts[i - 1][j] + grid[i][j];
                } else {
                    minCosts[i][j] = min(minCosts[i - 1][j], minCosts[i][j - 1]) + grid[i][j];
                }
            }
        }
        auto minCost = minCosts[rowCount - 1][colCount - 1];
        for (auto i = 0; i < rowCount; ++i) {
            delete[] minCosts[i];
        }
        delete[] minCosts;
        return minCost;
    }
};

int main() {
    Solution solution;
    vector<vector<int>> grid /* 7 */ {
            {1, 3, 1},
            {1, 5, 1},
            {4, 2, 1}
    };
    cout << solution.minPathSum(grid) << endl;
    return 0;
}