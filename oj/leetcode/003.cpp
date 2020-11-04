/**
 * 003 - 无重复字符的最长子串
 * @see
 * https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/description/
 *
 * 给定一个字符串，找出不含有重复字符的最长子串的长度。
 *
 * 示例：
 * 给定 "abcabcbb" ，没有重复字符的最长子串是 "abc" ，那么长度就是3。
 * 给定 "bbbbb" ，最长的子串就是 "b" ，长度是1。
 * 给定 "pwwkew" ，最长子串是 "wke" ，长度是3。请注意答案必须是一个子串，"pwke"
 * 是 子序列 而不是子串。
 *
 * 解题思路:
 * 对于不仅依赖前一个，而是有可能依赖不定数量的前N个元素的问题，建立适当的数据结构缓存可能用到的计
 * 算结果，并考虑清楚边界情况。
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
   public:
    int lengthOfLongestSubstring(string s) {
        vector<int> history(256, -1);
        int maxLength = 0, start = -1;
        for (auto i = 0; i != s.size(); ++i) {
            if (history[s[i]] > start) {
                start = history[s[i]];
            }
            history[s[i]] = i;
            maxLength = max(maxLength, i - start);
        }
        return maxLength;
    }
};

int main(int argc, char *argv[]) {
    Solution solution;

    auto start = chrono::high_resolution_clock::now();
    auto result = solution.lengthOfLongestSubstring("abcabcbb");
    auto end = chrono::high_resolution_clock::now();

    cout << result;
    cout << "\nin " << chrono::duration<float, milli>(end - start).count()
         << " ms." << endl;

    return 0;
}
