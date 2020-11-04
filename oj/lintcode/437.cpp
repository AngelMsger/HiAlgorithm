/**
 * 437 - 书籍复印
 *
 * 给定 n 本书, 第 i 本书的页数为 pages[i]. 现在有 k 个人来复印这些书籍, 而每个人只能复印编号连续的一段的书, 比如一个人可以复印 pages[0], pages[1], pages[2], 但是不可以只复印 pages[0], pages[2], pages[3] 而不复印 pages[1].
 *
 * 所有人复印的速度是一样的, 复印一页需要花费一分钟, 并且所有人同时开始复印. 怎样分配这 k 个人的任务, 使得这 n 本书能够被尽快复印完?
 *
 * 返回完成复印任务最少需要的分钟数.
 *
 * Example
 * 样例 1:
 *
 * 输入: pages = [3, 2, 4], k = 2
 * 输出: 5
 * 解释: 第一个人复印前两本书, 耗时 5 分钟. 第二个人复印第三本书, 耗时 4 分钟.
 * 样例 2:
 *
 * 输入: pages = [3, 2, 4], k = 3
 * 输出: 4
 * 解释: 三个人各复印一本书.
 * Challenge
 * 时间复杂度 O(nk)
 *
 * Notice
 * 书籍页数总和小于等于2147483647
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
     * @param pages: an array of integers
     * @param k: An integer
     * @return: an integer
     */
    int copyBooks(vector<int> &pages, int k) {
        auto pageCount = pages.size();
        if (pageCount == 0) return 0;
        auto **minCost = new int*[pageCount + 1];
        for (auto i = 0; i <= pageCount; ++i) {
            minCost[i] = new int[k];
            if (i == 0) {
                // 没有书, 所需时间为 0
                for (auto j = 0; j < k; ++j)
                    minCost[0][j] = 0;
            } else {
                // 只派 1 个人, 所需时间为页数和
                minCost[i][0] = minCost[i - 1][0] + pages[i - 1];
            }
        }
        // 截止当前书籍页数最大值(所需时间最多值)
        auto *maxPage = new int[pageCount];
        maxPage[0] = pages[0];
        for (auto i = 1; i < pageCount; ++i)
            maxPage[i] = max(maxPage[i - 1], pages[i]);

        int copyOfJ, cost;
        for (auto i = 1; i <= pageCount; ++i) {
            // 求书 [0, i - 1] 在派遣 j + 1 个人的前提下所需最少时间
            for (auto j = 1; j < k; ++j) {
                if (i <= j + 1) {
                    // 人多, 书少, 一人一本
                    minCost[i][j] = maxPage[i - 1];
                } else {
                    // 人少, 书多, 可划分
                    copyOfJ = 0;
                    minCost[i][j] = minCost[i][j - 1];
                    for (int l = i - 1; 0 <= l; --l) {
                        // [0, i - 1] 这些书中, 第 j 人读 [l, i - 1]
                        copyOfJ += pages[l];
                        cost = max(minCost[l][j - 1], copyOfJ);
                        if (cost < minCost[i][j])
                            minCost[i][j] = cost;
                    }
                }
            }
        }

        auto globalMinCost = minCost[pageCount][k - 1];
        for (auto i = 0; i <= pageCount; ++i)
            delete[] minCost[i];
        delete[] minCost;
        delete[] maxPage;
        return globalMinCost;
    }
};

int main() {
    Solution solution;
    vector<int> pages_1{3, 2, 4}, pages_2{3, 2, 4};
    auto k_1 = 2, k_2 = 3;
    cout
        << solution.copyBooks(pages_1, k_1) /* 5 */ << '\n'
        << solution.copyBooks(pages_2, k_2) /* 4 */ << endl;
    return 0;
}