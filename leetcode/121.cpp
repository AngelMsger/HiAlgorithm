/**
 * 121 - 买卖股票的最佳时机
 *
 * 给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。
 *
 * 如果你最多只允许完成一笔交易（即买入和卖出一支股票），设计一个算法来计算你所能获取的最大利润。
 *
 * 注意你不能在买入股票前卖出股票。
 *
 * 示例 1:
 *
 * 输入: [7,1,5,3,6,4]
 * 输出: 5
 * 解释: 在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
 *      注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格。
 * 示例 2:
 *
 * 输入: [7,6,4,3,1]
 * 输出: 0
 * 解释: 在这种情况下, 没有交易完成, 所以最大利润为 0。
 *
 * 解题思路：
 * 保留最低价格状态的动态规划。
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
    int maxProfit(vector<int> &prices) {
        auto dayCount = prices.size();
        if (dayCount == 0) return 0;
        auto minPriceUntilNow = new int[dayCount];
        auto maxProfit = 0;
        minPriceUntilNow[0] = prices[0];
        for (auto i = 1; i < dayCount; ++i) {
            minPriceUntilNow[i] = prices[i] < minPriceUntilNow[i - 1]
                                  ? prices[i]
                                  : minPriceUntilNow[i - 1];
            auto profit = prices[i] - minPriceUntilNow[i];
            if (maxProfit < profit) maxProfit = profit;
        }
        delete[] minPriceUntilNow;
        return maxProfit;
    }
};

int main() {
    Solution solution;
    vector<int> prices_1 /* 5 */ {7, 1, 5, 3, 6, 4}, prices_2/* 0 */{7, 6, 4, 3, 1};
    cout << solution.maxProfit(prices_1) << '\n'
         << solution.maxProfit(prices_2) << endl;
    return 0;
}