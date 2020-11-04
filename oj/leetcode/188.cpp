/**
 * 188 - 买卖股票的最佳时机 IV
 *
 * 给定一个数组，它的第 i 个元素是一支给定的股票在第 i 天的价格。
 * 设计一个算法来计算你所能获取的最大利润。你最多可以完成 k 笔交易。
 * 注意: 你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
 *
 * 示例 1:
 *
 * 输入: [2,4,1], k = 2
 * 输出: 2
 * 解释: 在第 1 天 (股票价格 = 2) 的时候买入，在第 2 天 (股票价格 = 4)
 * 的时候卖出，这笔交易所能获得利润 = 4-2 = 2 。
 * 示例 2:
 *
 * 输入: [3,2,6,5,0,3], k = 2
 * 输出: 7
 * 解释: 在第 2 天 (股票价格 = 2) 的时候买入，在第 3 天 (股票价格 = 6)
 *      的时候卖出, 这笔交易所能获得利润 = 6-2 = 4 。
 *      随后，在第 5 天 (股票价格 = 0) 的时候买入，在第 6 天 (股票价格 = 3)
 *      的时候卖出, 这笔交易所能获得利润 = 3-0 = 3 。
 *
 * 解题思路：
 * 与题目 123 基本一致，但由于变成了任意 K 比交易，因此当 K 足够大时，相当于
 * 退化成了题目 122，只需将所有上升区间差值求和即可。从测试用例来看，确实存在
 * K 值极大的测试用例，直接 new 数组会导致 memory exceed。
 * 由于第 i 天的状态仅依赖于第 i - 1 天，可以将申请整个表改为基于滚动数组。考虑到代
 * 码的可读性，我的代码没有做这种优化。
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
    int commonSolution(int transCount, vector<int>& prices) {
        auto dayCount = prices.size();          // 天数
        auto stageCount = 2 * transCount + 1;   // 阶段数

        // 0 或 1 天时间无法产生有效交易，直接返回。
        if (dayCount < 2) return 0;

        // 申请状态数组
        // profit[i][j] 表示前 i 天在第 i - 1 天为状态 j 下的收益
        auto **profit = new int *[dayCount + 1];
        for (auto i = 0; i <= dayCount; ++i)
            profit[i] = new int[stageCount];
        // 前 0 天在任意状态下的收益均为 0
        for (auto i = 0; i < 2; ++i)
            for (auto j = 0; j < stageCount; ++j) {
                profit[i][j] = 0;
            }

        for (auto i = 2; i <= dayCount; ++i) {
            for (auto j = 0; j < stageCount; ++j) {
                // 若停留在首次未买入状态，收益为 0
                if (j == 0) profit[i][j] = 0;
                    // 分类讨论今日状态来源及对收益的影响
                else {
                    int profitWhenKeep,     // 当今日状态来源与对昨日状态保持时的收益
                    profitWhenUpdate;   // 当今日状态来源于对昨日状态更新时的收益
                    auto profitToday = prices[i - 1] - prices[i - 2];
                    if ((j & 1) == 1) {
                        // 今日持有
                        profitWhenKeep = profit[i - 1][j] + profitToday;        // 持有 -> 持有，结算当日收益
                        // 累计收益为昨日同状态收益 + 今日收益
                        profitWhenUpdate = profit[i - 1][j - 1];                // 未持有 -> 持有，当日无收益
                        // 累计收益为昨日前一状态收益
                    } else {
                        // 今日未持有
                        profitWhenKeep = profit[i - 1][j];                      // 未持有 -> 未持有，当日无收益
                        // 累计收益为昨日同状态收益
                        profitWhenUpdate = profit[i - 1][j - 1] + profitToday;  // 持有 -> 未持有，结算当日收益
                        // 累计收益为昨日前一状态收益 + 今日收益
                    }
                    profit[i][j] = max(profitWhenKeep, profitWhenUpdate);
                }
            }
        }
        auto maxProfit = 0;
        for (auto i = 0; i < stageCount; ++i)
            if (profit[dayCount][i] > maxProfit)
                maxProfit = profit[dayCount][i];
        return maxProfit;
    }

    int optimizedSolution(int transCount, vector<int>& prices) {
        auto dayCount = prices.size();
        auto maxProfit = 0;
        for (auto i = 1; i < dayCount; ++i)
            if (prices[i - 1] < prices[i])
                maxProfit += prices[i] - prices[i - 1];
        return maxProfit;
    }
public:
    int maxProfit(int transCount, vector<int>& prices) {
        auto dayCount = prices.size();          // 天数
        if (dayCount / 2 < transCount)
            return this->optimizedSolution(transCount, prices);
        else
            return this->commonSolution(transCount, prices);
    }
};

int main() {
    Solution solution;
    vector<int> prices_1 /* 2 */ {2,4,1},
            prices_2 /* 7 */ {3,2,6,5,0,3};
    auto transCount_1 = 2, transCount_2 = 2;
    cout
            << solution.maxProfit(transCount_1, prices_1) << '\n'
            << solution.maxProfit(transCount_2, prices_2) << endl;
    return 0;
}
