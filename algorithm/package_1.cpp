/**
 * 动态规划专项 - 零一背包
 *
 * 问题描述：
 *
 * 已知 N 件物品，每件物品占用空间为 Ci，价值为 Vi。每件物品可以
 * 选择不取或取一个。求在背包容量为 C 的前提下背包能够承载的最大价
 * 值。
 *
 * 解题思路：
 *
 * 设 F[i][j] 为前 i 件物品在背包容量为 j 的情况下的最优解。则
 * 对于第 i 件物品，有取和不取两种选择，继而得到原始状态转移方程：
 * F[i][j] = max{F[i - 1][j], F[i - 1][j - Ci] + Vi}
 * 如下图：
 * --------------------------------------------------------
 *                          ...
 * --------------------------------------------------------
 * ...     F[i - 1][j - Ci]     ...     F[i - 1][j]     ...
 * --------------------------------------------------------
 * ...           ...            ...       F[i][j]       ...
 * --------------------------------------------------------
 *                          ...
 * --------------------------------------------------------
 * 因此违代码可以写为：
 * for i in range(0, N):
 *     for j in range(0, C):
 *         F[i][j] = max(
 *             F[i - 1][j],
 *             F[i - 1][j - C[i]] + W[i]
 *         )
 * 时间复杂度与空间复杂度均为 O(C * N)。
 * 进一步观察状态转移方程，可以发现 F[i] 仅依赖于 F[i - 1]。从表格
 * 中也容易看出 F[i][j] 仅依赖于其上一行左侧数据。而再之前的数据在
 * 计算进行至此时已失去作用。因此可以通过滚动数组的方式优化空间复杂度，
 * 得到优化后的状态转移方程：
 * F[j] = max{F[j], F[j - Ci] + Wi}
 * 此时内层循环必须从右至左遍历，已保证计算 F[j] 时，F[0...j - 1]
 * 仍未上一行数据。
 *
 * 补充：
 * 如果题目要求必须恰好填满背包。则只需在初始化时将 F 初始化为：
 * {0, -INF, -INF, ..., -INF}
 * 这种初始化方式可以通过以下描述理解：
 * 当 i = 0, j = 0 时，由于要求恰好填满背包，因此只有什么都不取符合
 * 要求。当 j = 1, 2, ..., C 时，由于不存在合法情况，因此以 -INF
 * 作为非法值标识。在 i 逐步增大的后续循环中，由于填满背包这种后续合法
 * 状态必然又之前的合法状态产生，因此算法可以继续进行。
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
        for (auto j = C; j >= COST[i]; --j) {
            F[j] = max(F[j], F[j - COST[i]] + VALUE[i]);
        }
    cout << F[C - 1] << endl;
    return 0;
}
