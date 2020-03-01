/**
 * 123 - 买卖股票的最佳时机 III
 *
 * 给定一个数组，它的第 i 个元素是一支给定的股票在第 i 天的价格。
 *
 * 设计一个算法来计算你所能获取的最大利润。你最多可以完成 两笔 交易。
 *
 * 注意: 你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
 *
 * 示例 1:
 *
 * 输入: [3,3,5,0,0,3,1,4]
 * 输出: 6
 * 解释: 在第 4 天（股票价格 = 0）的时候买入，在第 6 天（股票价格 = 3）的时候卖出，这笔交易所能获得利润 = 3-0 = 3 。
 *      随后，在第 7 天（股票价格 = 1）的时候买入，在第 8 天 （股票价格 = 4）的时候卖出，这笔交易所能获得利润 = 4-1 = 3 。
 * 示例 2:
 *
 * 输入: [1,2,3,4,5]
 * 输出: 4
 * 解释: 在第 1 天（股票价格 = 1）的时候买入，在第 5 天 （股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5-1 = 4 。  
 *      注意你不能在第 1 天和第 2 天接连购买股票，之后再将它们卖出。  
 *      因为这样属于同时参与了多笔交易，你必须在再次购买前出售掉之前的股票。
 * 示例 3:
 *
 * 输入: [7,6,4,3,1]
 * 输出: 0
 * 解释: 在这个情况下, 没有交易完成, 所以最大利润为 0。
 *
 * 解题思路：
 * 较复杂的序列型动态规划。如果把多次购买卖出在时间段上划分，以 2 次为例，大致可以表示为：
 * 未持有【1】-> 持有【2】-> 未持有【3】-> 持有【4】-> 未持有【5】
 * 若设允许买卖 K 次，即允许出现 K 个彼此分割的持有状态，则共有 2K + 1 个状态分段。
 * 对于任意一天，股民必然在这 2K + 1 个状态中的一种。
 * 之所以股民今天可以处于某一状态，只有可能是两种情况：
 * 1. 前一天已经是这种状态。
 * 2. 前一天是前一种状态，今天变化为当前状态。
 * 而根据前一状态和当前状态的不同，对收益的影响也不同：
 * 未持有 -> 未持有：当日不产生收益
 * 未持有 -> 持有：当日买入，不产生收益
 * 持有 -> 持有: 结算当日收益
 * 持有 -> 未持有: 当日卖出，结算收益
 */

#include <iostream>
#include <vector>

using namespace std;

static auto _ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

constexpr auto transCount = 2;

class Solution {
public:
    int maxProfit(vector<int> &prices) {
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
};

int main() {
    Solution solution;
    vector<int> prices_1 /* 6 */ {3, 3, 5, 0, 0, 3, 1, 4},
            prices_2 /* 4 */ {1, 2, 3, 4, 5},
            prices_3 /* 0 */ {7, 6, 4, 3, 1};
    cout
            << solution.maxProfit(prices_1) << '\n'
            << solution.maxProfit(prices_2) << '\n'
            << solution.maxProfit(prices_3) << endl;
    return 0;
}
