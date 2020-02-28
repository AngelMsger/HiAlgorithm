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
    int maxKilledEnemies(vector<vector<char>> &grid) {

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
