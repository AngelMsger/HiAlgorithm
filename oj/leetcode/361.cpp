/**
 * 361 - 炸弹袭击
 *
 * 原题目在 LeetCode 上为订阅题目，未订阅用户可以使用 LintCode。
 * LeetCode: https://leetcode.com/problems/bomb-enemy
 * LintCode: https://www.lintcode.com/problem/bomb-enemy
 *
 * 给定一个二维矩阵, 每一个格子可能是一堵墙 W,或者 一个敌人 E 或者空 0 (数字 '0'),
 * 返回你可以用一个炸弹杀死的最大敌人数. 炸弹会杀死所有在同一行和同一列没有墙阻隔的敌人。
 * 由于墙比较坚固，所以墙不会被摧毁.
 *
 * 示例：
 * 样例1
 *
 * 输入:
 * grid =[
 *      "0E00",
 *      "E0WE",
 *      "0E00"
 * ]
 * 输出: 3
 * 解释:
 * 把炸弹放在 (1,1) 能杀3个敌人
 * 样例2
 *
 * 输入:
 * grid =[
 *      "0E00",
 *      "EEWE",
 *      "0E00"
 * ]
 * 输出: 2
 * 解释:
 * P把炸弹放在 (0,0) 或 (0,3) 或 (2,0) 或 (2,3) 能杀2个敌人
 *
 * 注意事项：你只能在空的地方放置炸弹.
 *
 * 解题思路：
 * 1. 暴力求解：
 * 从每个坐标开始向 4 个方向展开遍历，统计结果后求最值。
 * 2. 最值坐标型动态规划：
 * 题目存在 4 个方向，任取一个坐标，如 (2, 2)，假设其是一个空地，那么在该位置放置炸弹后的爆炸范围实际上由
 * 4 个方向共同决定，即在表格中，(i, j) 处的最终结果不仅由其左方，上方或左上方的数据决定。那么沿着这个思路
 * 似乎找不到"规模更小的子问题"。但 (i, j) 处的爆炸影响，和 4 个方向是线性叠加的关系，依次求出 4 个方向
 * 可以炸死敌人的数量后求和，即可得到在该点能够炸死的全部敌人数。而求解任意单个方向的炸死敌人数量，则可转化为
 * 动态规划可解(因为影响仅来自该方向上的数据)的问题。
 * 最后一步：以求【上方】为例，singleDirection[i][j] 表示在 (i, j) 处可以炸死上方多少个敌人。
 *         首先，如果该位置为墙，则不可放置炸弹，炸死上方敌人数应为 0。
 *         其次，如果该位置为空地，则其可炸死上方敌人数与 (i - 1, 0) 一致，若 i == 0，则为 0。
 *         最后，如果该位置为敌人，虽然理论上不可放置炸弹，但考虑到题目描述中，炸弹对敌人有穿透效果，因此为
 *              了让累加值在此处不会丢失，因此保留 (i - 1, 0) 一致。另外，由于我们多杀死了一个敌人，因
 *              此要在这个值的基础上加 1。若 i == 0，则 singleDrection[i][j] = 1。
 *         累加 4 个方向，即可得到每个位置能够杀死敌人的数量。对于有敌人的格子，因为我们每个单方向都加了 1，
 *         最终会导致重复计算，但因为这种格子本身不符合题目炸弹只能放置在空地的要求，因此最后求最值的时候会
 *         被过滤掉，因此此处无需额外处理。
 * 得到子结构：见上方描述。
 * 得到递推式：见上方描述。
 * 边界条件：见上方描述。
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
private:
    void matAdd(int **result, int **value, int rowCount, int colCount) {
        for (auto i = 0; i < rowCount; ++i) {
            for (auto j = 0; j < colCount; ++j) {
                result[i][j] += value[i][j];
            }
        }
    }
public:
    int maxKilledEnemies(vector<vector<char>> &grid) {
        auto rowCount = grid.size();
        if (rowCount == 0) return 0;
        auto colCount = grid[0].size();
        if (colCount == 0) return 0;
        int **singleDirection = new int*[rowCount];
        int **multiDirection = new int*[rowCount];
        for (auto i = 0; i < rowCount; ++i) {
            singleDirection[i] = new int[colCount];
            multiDirection[i] = new int[colCount];
            memset(multiDirection[i], 0, colCount * sizeof(int));
        }

        // Up
        for (auto i = 0; i < rowCount; ++i) {
            for (auto j = 0; j < colCount; ++j) {
                if (grid[i][j] == 'W') {
                    singleDirection[i][j] = 0;
                } else if (grid[i][j] == '0') {
                    if (i == 0) {
                        singleDirection[i][j] = 0;
                    } else {
                        singleDirection[i][j] = singleDirection[i - 1][j];
                    }
                } else {
                    if (i == 0) {
                        singleDirection[i][j] = 1;
                    }else {
                        singleDirection[i][j] = singleDirection[i - 1][j] + 1;
                    }
                }
            }
        }
        this->matAdd(multiDirection, singleDirection, rowCount, colCount);

        // Right
        for (auto i = 0; i < rowCount; ++i) {
            for (int j = (int)(colCount - 1); 0 <= j; --j) {
                if (grid[i][j] == 'W') {
                    singleDirection[i][j] = 0;
                } else if (grid[i][j] == '0') {
                    if (j == colCount - 1) {
                        singleDirection[i][j] = 0;
                    } else {
                        singleDirection[i][j] = singleDirection[i][j + 1];
                    }
                } else {
                    if (j == colCount - 1) {
                        singleDirection[i][j] = 1;
                    } else {
                        singleDirection[i][j] = singleDirection[i][j + 1] + 1;
                    }
                }
            }
        }
        this->matAdd(multiDirection, singleDirection, rowCount, colCount);

        // Down
        for (int i = (int)(rowCount - 1); 0 <= i; --i) {
            for (auto j = 0; j < colCount; ++j) {
                if (grid[i][j] == 'W') {
                    singleDirection[i][j] = 0;
                } else if (grid[i][j] == '0') {
                    if (i == rowCount - 1) {
                        singleDirection[i][j] = 0;
                    } else {
                        singleDirection[i][j] = singleDirection[i + 1][j];
                    }
                } else {
                    if (i == rowCount - 1) {
                        singleDirection[i][j] = 1;
                    } else {
                        singleDirection[i][j] = singleDirection[i + 1][j] + 1;
                    }
                }
            }
        }
        this->matAdd(multiDirection, singleDirection, rowCount, colCount);

        // Left
        for (auto i = 0; i < rowCount; ++i) {
            for (auto j = 0; j < colCount; ++j) {
                if (grid[i][j] == 'W') {
                    singleDirection[i][j] = 0;
                } else if (grid[i][j] == '0') {
                    if (j == 0) {
                        singleDirection[i][j] = 0;
                    } else {
                        singleDirection[i][j] = singleDirection[i][j - 1];
                    }
                } else {
                    if (j == 0) {
                        singleDirection[i][j] = 1;
                    } else {
                        singleDirection[i][j] = singleDirection[i][j - 1] + 1;
                    }
                }
            }
        }
        this->matAdd(multiDirection, singleDirection, rowCount, colCount);

        auto maxKilled = 0;
        for (auto i = 0; i < rowCount; ++i) {
            for (auto j = 0; j < colCount; ++j) {
                if (grid[i][j] == '0' && multiDirection[i][j] > maxKilled) {
                    maxKilled = multiDirection[i][j];
                }
            }
            delete[] singleDirection[i];
            delete[] multiDirection[i];
        }
        delete[] singleDirection;
        delete[] multiDirection;
        return maxKilled;
    }
};

int main() {
    Solution solution;
    vector<vector<char>> grid /* 3 */ {
        {'0', 'E', '0', '0'},
        {'E', '0', 'W', 'E'},
        {'0', 'E', '0', '0'}
    };
    cout << solution.maxKilledEnemies(grid) << endl;
    return 0;
}
