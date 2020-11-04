/**
 * 92 - 背包问题
 *
 * 在n个物品中挑选若干物品装入背包，最多能装多满？假设背包的大小为m，每个物品的大小为A[i]
 *
 * Example
 * 样例 1:
 * 	输入:  [3,4,8,5], backpack size=10
 * 	输出:  9
 *
 * 样例 2:
 * 	输入:  [2,3,5,7], backpack size=12
 * 	输出:  12
 *
 * Challenge
 * Notice
 * 你不可以将物品进行切割。
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
     * @return: The maximum size
     */
    int backPack(int m, vector<int> &A) {
        auto itemSize = A.size();
        if (itemSize == 0) return 0;
        auto **maxValue = new int*[itemSize + 1];
        for (auto i = 0; i <= itemSize; ++i) {
            maxValue[i] = new int[m + 1];
            maxValue[i][0] = 0;
        }
        memset(maxValue[0], 0, (m + 1) * sizeof(int));

        int currentItemWeight;
        for (auto i = 1; i <= itemSize; ++i) {
            for (auto j = 1; j <= m; ++j) {
                currentItemWeight = A[i - 1];
                if (j < currentItemWeight) {
                    // 当前物品装不下
                    maxValue[i][j] = maxValue[i - 1][j];
                } else {
                    maxValue[i][j] = max(
                            // 取当前物品
                            maxValue[i - 1][j - currentItemWeight] + currentItemWeight,
                            // 不取当前物品
                            maxValue[i - 1][j]
                    );
                }
            }
        }

        auto globalMaxValue = maxValue[itemSize][m];
        for (auto i = 0; i <= itemSize; ++i)
            delete[] maxValue[i];
        delete[] maxValue;
        return globalMaxValue;
    }
};

int main() {
    Solution solution;
    vector<int>
        A_1 {3, 4, 8, 5},
        A_2 {2, 3, 5, 7},
        A_3 {3, 9, 5, 2};
    auto m_1 = 10, m_2 = 12, m_3 = 10;
    cout
        << solution.backPack(m_1, A_1) /* 9 */ << '\n'
        << solution.backPack(m_2, A_2) /* 12 */ << '\n'
        << solution.backPack(m_3, A_3) /* 10 */ << endl;
    return 0;
}
