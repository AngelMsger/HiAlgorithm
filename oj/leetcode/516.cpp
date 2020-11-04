/**
 * 516 - 最长回文子序列
 *
 * 给定一个字符串s，找到其中最长的回文子序列。可以假设s的最大长度为1000。
 *
 * 示例 1:
 * 输入: "bbbab"
 * 输出: 4
 * 一个可能的最长回文子序列为 "bbbb"。
 *
 * 示例 2:
 * 输入: "cbbd"
 * 输出: 2
 * 一个可能的最长回文子序列为 "bb"。
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
    int longestPalindromeSubseq(string s) {
        // edge cond
        auto sSize = s.size();
        if (sSize == 0) return 0;
        // init
        auto **longest = new unsigned int*[sSize];
        for (auto i = 0u; i < sSize; ++i) {
            longest[i] = new unsigned  int[sSize];
            longest[i][i] = 1;
        }
        // calc
        for (auto width = 2; width <= sSize; ++width) {
            for (auto i = 0u; i < sSize; ++i) {
                unsigned int j = i + width - 1;
                if (j < sSize) {
                    if (s[i] == s[j]) {
                        longest[i][j] = 2 + ((j == i + 1) ? 0 : longest[i + 1][j - 1]);
                    } else {
                        longest[i][j] = max(
                                longest[i][j - 1], longest[i + 1][j]
                        );
                    }
                } else break;
            }
        }
        // clean
        auto global = longest[0][sSize - 1];
        for (auto i = 0u; i < sSize; ++i) {
            delete[] longest[i];
        }
        delete[] longest;
        return global;
    }
};

int main() {
    Solution solution;
    cout
         << solution.longestPalindromeSubseq("bbbab") /* 4 */ << '\n'
         << solution.longestPalindromeSubseq("cbbd") /* 2 */ << endl;
    return 0;
}
