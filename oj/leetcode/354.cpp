/**
 * 354 - 俄罗斯套娃信封问题
 *
 * 给定一些标记了宽度和高度的信封，宽度和高度以整数对形式 (w, h) 出现。当另一个信封的宽度和高度都比这个信封大的时候，这个信封就可以放进另一个信封里，如同俄罗斯套娃一样。
 *
 * 请计算最多能有多少个信封能组成一组“俄罗斯套娃”信封（即可以把一个信封放到另一个信封里面）。
 *
 * 说明:
 * 不允许旋转信封。
 *
 * 示例:
 *
 * 输入: envelopes = [[5,4],[6,4],[6,7],[2,3]]
 * 输出: 3
 * 解释: 最多信封的个数为 3, 组合为: [2,3] => [5,4] => [6,7]。
 *
 * 解题思路：
 * 题目 300 的变种。按某一边排序后求另一边的最长递增子序列即可。
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
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        auto envelopeCount = envelopes.size();
        if (envelopeCount == 0) return 0;

        sort(
            envelopes.begin(), envelopes.end(),
            [](
                const vector<int> &lhs,
                const vector<int> &rhs
            ) {
                return lhs[0] < rhs[0];
            }
        );

        auto globalMaxEnvelopes = 1;

        auto maxEnvelopes = new int[envelopeCount];
        maxEnvelopes[0] = 1;
        for (auto i = 1; i < envelopeCount; ++i) {
            maxEnvelopes[i] = 1;
            for (auto j = 0; j < i; j++) {
                if (
                    envelopes[j][0] < envelopes[i][0] &&
                    envelopes[j][1] < envelopes[i][1] &&
                    maxEnvelopes[i] < maxEnvelopes[j] + 1
                ) {
                    maxEnvelopes[i] = maxEnvelopes[j] + 1;
                }
            }
            if (globalMaxEnvelopes < maxEnvelopes[i]) {
                globalMaxEnvelopes = maxEnvelopes[i];
            }
        }

        delete[] maxEnvelopes;
        return globalMaxEnvelopes;
    }
};

int main() {
    Solution solution;
    vector<vector<int>> /* 3 */ envelopes_1;
    envelopes_1.push_back({5, 4});
    envelopes_1.push_back({6, 4});
    envelopes_1.push_back({6, 7});
    envelopes_1.push_back({2, 3});
    vector<vector<int>> /* 3 */ envelopes_2;
    envelopes_2.push_back({1, 3});
    envelopes_2.push_back({3, 5});
    envelopes_2.push_back({6, 7});
    envelopes_2.push_back({6, 8});
    envelopes_2.push_back({8, 4});
    envelopes_2.push_back({9, 5});
    cout
//        << solution.maxEnvelopes(envelopes_1) << '\n'
        << solution.maxEnvelopes(envelopes_2) << endl;
    return 0;
}
