/**
 * 动态规划专项 - 完全背包
 *
 * 问题描述：
 *
 * 与零一背包类似，但每个物品不再限于只能取 0 或 1 件，而是可以
 * 取任意数量。
 *
 * 解题思路：
 *
 * 可以通过将物品 i 拆分为若干个，从而将此问题转化为零一背包问题。
 * 此时时间复杂度为 O(C * N * (V / Ci))。但此题存在思路如下的
 * 更优解法：
 * 仅需调整零一背包实现代码中 j 的遍历顺序为从左至右即可。在零一
 * 背包问题中之所以反向遍历，是为了在计算 F[j] 时，
 * F[0 ... j - 1] 中的实际值仍为上一行数据，即对应 i - 1 而非
 * i，从而保证 F[j] 依赖的值计算过程中绝对没有物品 i 的参与。而
 * 在完全背包中并没有这个限制，如果以正向遍历，则
 * F[0 ... j - 1] 在逐步遍历过程中已经尝试过尽可能多的物品 i，
 * 进而 F[j] 可以得到我们期待的结果。
 *
 * 优化技巧：
 * 若 C_i1 > C_i2 && V_i1 <= V_i2，则可将物品 i1 从列表中移
 * 除，原因非常明显，物品 i1 总是能够被占用空间更小但价值更高的物
 * 品 i2 所取代。
 */

#include <cmath>
#include <iostream>

using namespace std;

// 背包容量
constexpr unsigned int C = 12;
// 物品数量
constexpr unsigned int N = 6;
// 物品代价数组
constexpr unsigned int COST[] = {3, 2, 6, 4, 5, 1};
// 物品价值数组
constexpr unsigned int VALUE[] = {2, 1, 3, 4, 1, 2};

int main(int argc, char *argv[]) {
    unsigned int F[C + 1] = {0};
    for (auto i = 0; i < N; ++i)
        for (auto j = COST[i]; j <= C; ++j) {
            F[j] = max(F[j], F[j - COST[i]] + VALUE[i]);
        }
    cout << F[C] << endl;
    return 0;
}
