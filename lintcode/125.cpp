/**
 * 125 - 背包问题 II
 *
 * 有 n 个物品和一个大小为 m 的背包. 给定数组 A 表示每个物品的大小和数组 V 表示每个物品的价值.
 * 问最多能装入背包的总价值是多大?
 *
 * Example
 *
 * 样例 1:
 * 输入: m = 10, A = [2, 3, 5, 7], V = [1, 5, 2, 4]
 * 输出: 9
 * 解释: 装入 A[1] 和 A[3] 可以得到最大价值, V[1] + V[3] = 9
 *
 * 样例 2:
 * 输入: m = 10, A = [2, 3, 8], V = [2, 5, 8]
 * 输出: 10
 * 解释: 装入 A[0] 和 A[2] 可以得到最大价值, V[0] + V[2] = 10
 *
 * Challenge
 * O(nm) 空间复杂度可以通过, 不过你可以尝试 O(m) 空间复杂度吗?
 *
 * Notice
 * A[i], V[i], n, m 均为整数
 * 你不能将物品进行切分
 * 你所挑选的要装入背包的物品的总大小不能超过 m
 * 每个物品只能取一次
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
    /**
     * @param m: An integer m denotes the size of a backpack
     * @param A: Given n items with size A[i]
     * @param V: Given n items with value V[i]
     * @return: The maximum value
     */
    int backPackII(int m, vector<int> &A, vector<int> &V) {
        auto costCount = A.size();
        auto valueCount = V.size();
        if (costCount != valueCount) return -1;
        if (costCount == 0) return 0;
        // init
        // max value with total cost j
        auto **maxValues = new int*[costCount + 1];
        for (auto i = 0; i <= costCount; ++i) {
            maxValues[i] = new int[m + 1];
            maxValues[i][0] = 0;
        }
        memset(maxValues[0], 0, (m + 1) * sizeof(int));
        // calculate
        for (auto i = 1; i <= costCount; ++i) {
            auto valueOfI = V[i - 1];
            auto costOfI = A[i - 1];
            for (auto j = 1; j <= m; ++j) {
                if (costOfI <= j) {
                    auto withI = maxValues[i - 1][j - costOfI] + valueOfI;
                    auto withoutI = maxValues[i - 1][j];
                    maxValues[i][j] = max(withI, withoutI);
                } else {
                    maxValues[i][j] = maxValues[i - 1][j];
                }
            }
        }
        auto maxValue = maxValues[costCount][m];
        // release
        for (auto i = 0; i <= costCount; ++i)
            delete[] maxValues[i];
        delete[] maxValues;
        return maxValue;
    }
};

int main() {
    vector<int> A_1{2, 3, 5, 7}, V_1{1, 5, 2, 4};
    vector<int> A_2{2, 3, 8}, V_2{2, 5, 8};
    auto m_1 = 10, m_2 = 10;
    Solution solution;
    cout
         << solution.backPackII(m_1, A_1, V_1) /* 9 */ << '\n'
         << solution.backPackII(m_2, A_2, V_2) /* 10 */ << endl;
    return 0;
}