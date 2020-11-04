/**
 * 132 - 分割回文串
 *
 * 给定一个字符串 s，将 s 分割成一些子串，使每个子串都是回文串。
 *
 * 返回符合要求的最少分割次数。
 *
 * 示例:
 *
 * 输入: "aab"
 * 输出: 1
 * 解释: 进行一次分割就可将 s 分割成 ["aa","b"] 这样两个回文子串。
 */

#include <iostream>
#include <climits>

using namespace std;

static auto _ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    int minCut(string s) {
        auto charCount = s.size();
        if (charCount == 0) return 0;
        auto minCut = new int[charCount + 1];
        minCut[0] = -1;
        for (auto i = 1; i <= charCount; ++i) {
            minCut[i] = INT_MAX;
            for (auto j = 0; j <= i - 1; ++j) {
                auto l = j, r = i - 1;
                while (l < r && s[l] == s[r]) {
                    l += 1;
                    r -= 1;
                }
                if (r <= l && minCut[j] + 1 < minCut[i])
                    minCut[i] = minCut[j] + 1;
            }
        }
        auto globalMinCut = minCut[charCount];
        delete[] minCut;
        return globalMinCut;
    }
};

int main() {
    Solution solution;
    cout
        << solution.minCut("ab" /* 1 */) << '\n'
        << solution.minCut("aa" /* 0 */) << '\n'
        << solution.minCut("aab" /* 1 */) << endl;
    return 0;
}
