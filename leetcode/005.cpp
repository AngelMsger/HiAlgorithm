/**
 * 005 - 最长回文子串
 * @see
 * https://leetcode-cn.com/problems/longest-palindromic-substring/description/
 *
 * 给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为1000。
 *
 * 示例 1：
 * 输入: "babad"
 * 输出: "bab"
 *
 * 注意: "aba"也是一个有效答案。
 *
 * 示例 2：
 * 输入: "cbbd"
 * 输出: "bb"
 *
 * 解题思路:
 * 最直接的方式是求得所有子串(递归)，并判断是否为回文串，时间复杂度为O(n^3)。
 * 更好的想法是遍历字符串中的每一个间隙并向两边扩展，或其优化版本Manacher(马拉车)算法，以及动态规划。
 *
 * Manacher算法核心思想:
 * 如果待匹配位置处于已成功匹配过的回文串内，则其关于该回文串中心对称位置的回文信息可以作为本次匹配的基
 * 础而被重复利用。
 *
 * @see https://segmentfault.com/a/1190000003914228
 * @see
 * https://graysonliu.github.io/2017/10/09/23.%20LeetCode%20-%205.%20%E6%B1%82
 * %E6%9C%80%E9%95%BF%E5%9B%9E%E6%96%87%E5%AD%90%E4%B8%B2%E7%9A%84Manacher%E7%AE%97
 * %E6%B3%95/
 */

#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

static auto _ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
   private:
    string usingDP(const string &s) {
        const auto n = s.size();
        // NOTICE: std::vector<bool> is DEPRECATED, carefully to use it.
        auto history = vector<vector<bool>>(n, vector<bool>(n, false));
        auto maxLength = 0, beginOffset = 0, endOffset = 0;
        for (auto i = 0; i < n; ++i) {
            for (auto j = i; j >= 0; --j) {
                if (s[i] == s[j] && (i - j < 2 || history[i - 1][j + 1])) {
                    history[i][j] = true;
                    auto length = i - j + 1;
                    if (length > maxLength) {
                        maxLength = length;
                        beginOffset = j;
                        endOffset = i + 1;
                    }
                }
            }
        }
        auto begin = s.cbegin();
        return string(begin + beginOffset, begin + endOffset);
    }

    string usingManacher(const string &s) {
        // ma: 填充后的数组
        // mp: 该位置回文半径
        // mx: 已得到的末端最远(但不一定就是最长)的回文串的最后一个字符的位置
        // id: 已得到的末端最远(但不一定就是最长)的回文串的中心字符的位置
        auto length = s.size() * 2 + 1;
        vector<char> ma(length, '#');
        for (auto i = 0; i < s.size(); ++i) {
            ma[i * 2 + 1] = s[i];
        }
        vector<int> mp(length, 0);
        auto mx = 0, id = 0;
        for (auto i = 0; i < length; ++i) {
            mp[i] = i < mx ? min(mp[2 * id - i], mx - i) : 1;
            while (i + mp[i] < ma.size() && i + mp[i] > 0 &&
                   ma[i + mp[i]] == ma[i - mp[i]])
                ++mp[i];
            if (i + mp[i] > mx) {
                mx = i + mp[i];
                id = i;
            }
        }
        auto center = max_element(mp.cbegin(), mp.cend()) - mp.cbegin();
        auto radius = mp[center] - 1;
        return string(s.cbegin() + (center - radius) / 2,
                      s.cbegin() + (center + radius) / 2);
    }

   public:
    string longestPalindrome(string s) { return usingManacher(s); }
};

int main(int argc, char *argv[]) {
    Solution solution;

    auto start = chrono::high_resolution_clock::now();
    auto result = solution.longestPalindrome("");
    auto end = chrono::high_resolution_clock::now();

    cout << result;
    cout << "\nin " << chrono::duration<float, milli>(end - start).count()
         << " ms." << endl;

    return 0;
}
