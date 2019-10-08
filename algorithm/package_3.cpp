/**
 * 动态规划专项 - 多重背包
 *
 * 问题描述：
 *
 * 与零一背包类似，但每个物品不再限于只能取 0 或 1 件，而是可以
 * 取有限数量。
 *
 * 解题思路：
 *
 * 可以通过将物品 i 拆分为若干个，从而将此问题转化为零一背包问题。
 * 此时时间复杂度为 O(C * N * M)。与完全背包类似，本题存在以下
 * 优化解法：
 * 受二进制思想启发，对于 Mi 件物品，可以将其拆分为：
 * 1，2，4，...，2^(k - 1), Mi - 2^k + 1 件物品，易知取 1
 * ～ Mi 件物品均可由组合上述拆分结果来标示，因此时间复杂度降低为
 * O(C * N * log M)。
 */

#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

// 背包容量
constexpr int C = 12;
// 物品数量
constexpr int N = 6;
// 物品代价数组
constexpr int COST[] = {3, 2, 6, 4, 5, 1};
// 物品价值数组
constexpr int VALUE[] = {2, 1, 3, 4, 1, 2};
// 物品数量数组
constexpr int MAX[] = {3, 2, 1, 3, 1, 2};

int main(int argc, char *argv[]) {
    vector<int> cost, value;
    for (auto i = 0; i < N; ++i) {
        auto c = COST[i], v = VALUE[i], m = MAX[i];
        auto u = static_cast<int>(log2(m));
        for (auto j = 0; j < u; ++j) {
            auto p = static_cast<int>(pow(2, j));
            cost.push_back(c * p);
            value.push_back(v * p);
        }
        auto s = m - pow(2, u) + 1;
        for (auto j = 0; j < s; ++j) {
            cost.push_back(c);
            value.push_back(v);
        }
    }
    auto n = cost.size();
    unsigned int F[C + 1] = {0};
    for (auto i = 0; i < n; ++i)
        for (auto j = C; j >= cost[i]; --j) {
            F[j] = max(F[j], F[j - cost[i]] + value[i]);
        }
    cout << F[C] << endl;
    return 0;
}
