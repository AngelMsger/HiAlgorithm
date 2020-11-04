/**
 * 322 - Coin Change
 * 给定不同面额的硬币 coins 和一个总金额 amount。编写一个函数来计算可以凑成总金额
 * 所需的最少的硬币个数。如果没有任何一种硬币组合能组成总金额，返回 -1。
 *
 * 示例 1:
 * 输入: coins = [1, 2, 5], amount = 11
 * 输出: 3
 * 解释: 11 = 5 + 5 + 1
 *
 * 示例 2:
 * 输入: coins = [2], amount = 3
 * 输出: -1
 * 说明:
 * 你可以认为每种硬币的数量是无限的。
 *
 * 解题思路：
 * 动态规划经典题目，符合求最值场景。
 * 最后一步：以示例数据说明，为了凑出 11，则必须能够凑出 11 - 1，11 - 2，11 - 5
 *         三者之一，且所需硬币数量为三者中较小这加 1(最后一枚)。
 * 得到子结构：设 minCounts[i] 为凑和为 i 所需硬币最少数量。
 * 得到递推式：minCounts[i] = min{ minCounts[i - 1], minCounts[i - 2], minCounts[i - 5] } + 1。
 * 考虑边界条件：minCounts[0] = 0，minCounts 下标应大于等于 0。
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
    int coinChange(vector<int>& coins, int amount) {
        auto *minCounts = new int[amount + 1];
        auto coinClasses = coins.size();
        minCounts[0] = 0;
        for (auto i = 1; i <= amount; ++i) {
            minCounts[i] = INT_MAX;
            // test every cases
            for (auto j = 0; j < coinClasses; ++j) {
                auto coin = coins[j];
                if (
                    i - coin >= 0 &&
                    // can be optimized
                    minCounts[i - coin] != INT_MAX &&
                    minCounts[i - coin] + 1 < minCounts[i]
                ) {
                    minCounts[i] = minCounts[i - coin] + 1;
                }
            }
        }
        auto resultValue = minCounts[amount] == INT_MAX ? -1 : minCounts[amount];
        delete[] minCounts;
        return resultValue;
    }
};

int main() {
    Solution solution;
    vector<int> coins {1, 2, 5};
    int amount = 11;
    cout << solution.coinChange(coins, amount) << endl;
    return 0;
}