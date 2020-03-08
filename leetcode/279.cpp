/**
 * 279 - 完全平方数
 * 给定正整数 n，找到若干个完全平方数（比如 1, 4, 9, 16, ...）使得它们的和等于 n。你需要让组成和的完全平方数的个数最少。
 *
 * 示例 1:
 *
 * 输入: n = 12
 * 输出: 3
 * 解释: 12 = 4 + 4 + 4.
 * 示例 2:
 *
 * 输入: n = 13
 * 输出: 2
 * 解释: 13 = 4 + 9.
 */

#include <iostream>

using namespace std;

static auto _ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    int numSquares(int n) {
        auto *numSquares = new int[n + 1];
        numSquares[0] = 0;
        numSquares[1] = 1;
        for (auto i = 2; i <= n; ++i) {
            numSquares[i] = INT_MAX;
            for (auto j = 1; j * j <= i; ++j)
                if (numSquares[i - j * j] + 1 < numSquares[i])
                    numSquares[i] = numSquares[i - j * j] + 1;
        }
        auto components = numSquares[n];
        delete[] numSquares;
        return components;
    }
};

int main() {
    Solution solution;
    cout
            << solution.numSquares(12) << '\n'
            << solution.numSquares(13) << endl;
    return 0;
}