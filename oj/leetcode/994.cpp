/**
 * 994 - 腐烂的橘子
 *
 * 在给定的网格中，每个单元格可以有以下三个值之一：
 * 值 0 代表空单元格；
 * 值 1 代表新鲜橘子；
 * 值 2 代表腐烂的橘子。
 * 每分钟，任何与腐烂的橘子（在 4 个正方向上）相邻的新鲜橘子都会腐烂。
 *
 * 返回直到单元格中没有新鲜橘子为止所必须经过的最小分钟数。如果不可能，返回 -1。
 *
 * 示例 1：
 * 输入：[[2,1,1],[1,1,0],[0,1,1]]
 * 输出：4
 *
 * 示例 2：
 * 输入：[[2,1,1],[0,1,1],[1,0,1]]
 * 输出：-1
 * 解释：左下角的橘子（第 2 行， 第 0 列）永远不会腐烂，因为腐烂只会发生在 4 个正向上。
 *
 * 示例 3：
 * 输入：[[0,2]]
 * 输出：0
 * 解释：因为 0 分钟时已经没有新鲜橘子了，所以答案就是 0 。
 *
 * 提示：
 * 1 <= grid.length <= 10
 * 1 <= grid[0].length <= 10
 * grid[i][j] 仅为 0、1 或 2
 *
 * 解题思路:
 * 按题目描述进行模拟和状态判定即可.
 */

#include <iostream>
#include <vector>
#include <deque>

using namespace std;

static auto _ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
private:
    int stlSolution(vector<vector<int>>& grid) {
        auto rowCount = grid.size();
        if (rowCount == 0) return -1;
        auto colCount = grid[0].size();
        if (colCount == 0) return -1;

        deque<pair<int, int>> rotted;
        auto fresh = 0, seniority = 0;
        for (auto i = 0; i < rowCount; ++i) {
            for (auto j = 0; j < colCount; ++j) {
                if (grid[i][j] == 1) ++fresh;
                else if (grid[i][j] == 2) rotted.emplace_back(i, j);
            }
        }
        while (fresh != 0 && !rotted.empty()) {
            auto rottedCount = rotted.size();
            for (auto i = 0; i < rottedCount; ++i) {
                auto orange = rotted.front();
                rotted.pop_front();
                // left
                if (0 < orange.first && grid[orange.first - 1][orange.second] == 1) {
                    grid[orange.first - 1][orange.second] = 2;
                    rotted.emplace_back(orange.first - 1, orange.second);
                    --fresh;
                }
                // right
                if (orange.first + 1 < rowCount && grid[orange.first + 1][orange.second] == 1) {
                    grid[orange.first + 1][orange.second] = 2;
                    rotted.emplace_back(orange.first + 1, orange.second);
                    --fresh;
                }
                // top
                if (0 < orange.second && grid[orange.first][orange.second - 1] == 1) {
                    grid[orange.first][orange.second - 1] = 2;
                    rotted.emplace_back(orange.first, orange.second - 1);
                    --fresh;
                }
                // bottom
                if (orange.second + 1 < colCount && grid[orange.first][orange.second + 1] == 1) {
                    grid[orange.first][orange.second + 1] = 2;
                    rotted.emplace_back(orange.first, orange.second + 1);
                    --fresh;
                }
            }
            ++seniority;
        }
        return fresh == 0 ? seniority : -1;
    }
    int optimizedSolution(vector<vector<int>>& grid) {
        auto rowCount = grid.size();
        auto colCount = grid[0].size();
        int xQueue[101], yQueue[101];
        auto head = 0, tail = 0;
        auto fresh = 0, seniority = 0;
        for (auto i = 0; i < rowCount; ++i) {
            for (auto j = 0; j < colCount; ++j) {
                if (grid[i][j] == 1) ++fresh;
                else if (grid[i][j] == 2) {
                    xQueue[tail] = i;
                    yQueue[tail++] = j;
                }
            }
        }
        auto x = 0, y = 0;
        int rottedCount;
        while (fresh != 0 && head != tail) {
            rottedCount = tail - head;
            for (auto i = 0; i < rottedCount; ++i) {
                x = xQueue[head];
                y = yQueue[head++];
                // left
                if (0 < x && grid[x - 1][y] == 1) {
                    grid[x - 1][y] = 2;
                    xQueue[tail] = x - 1;
                    yQueue[tail++] = y;
                    --fresh;
                }
                // right
                if (x + 1 < rowCount && grid[x + 1][y] == 1) {
                    grid[x + 1][y] = 2;
                    xQueue[tail] = x + 1;
                    yQueue[tail++] = y;
                    --fresh;
                }
                // top
                if (0 < y && grid[x][y - 1] == 1) {
                    grid[x][y - 1] = 2;
                    xQueue[tail] = x;
                    yQueue[tail++] = y - 1;
                    --fresh;
                }
                // bottom
                if (y + 1 < colCount && grid[x][y + 1] == 1) {
                    grid[x][y + 1] = 2;
                    xQueue[tail] = x;
                    yQueue[tail++] =y + 1;
                    --fresh;
                }
            }
            ++seniority;
        }
        return fresh == 0 ? seniority : -1;
    }
public:
    int orangesRotting(vector<vector<int>>& grid) {
        optimizedSolution(grid);
    }
};

int main() {
    Solution solution;
    vector<vector<int>> grid_1;
    grid_1.push_back({2, 1, 1});
    grid_1.push_back({1, 1, 0});
    grid_1.push_back({0, 1, 1});
    vector<vector<int>> grid_2;
    grid_2.push_back({1, 2});
    cout
        << solution.orangesRotting(grid_1) << '\n'
        << solution.orangesRotting(grid_2) << endl;
    return 0;
}
