/**
 * 014 - 最长公共前缀
 * @see https://leetcode-cn.com/problems/longest-common-prefix/description/
 *
 * 编写一个函数来查找字符串数组中的最长公共前缀。
 * 如果不存在公共前缀，返回空字符串 ""。
 *
 * 示例 1:
 * 输入: ["flower","flow","flight"]
 * 输出: "fl"
 *
 * 示例 2:
 * 输入: ["dog","racecar","car"]
 * 输出: ""
 * 解释: 输入不存在公共前缀。
 *
 * 说明:
 * 所有输入只包含小写字母 a-z 。
 *
 * 解题思路:
 * 遍历比对数组中的字符串即可就得结果。
 */

#include <bits/stdc++.h>
using namespace std;

static auto _ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty()) return "";
        auto minSize = strs[0].size();
        for (const auto &str : strs) if (str.size() < minSize) minSize = str.size();
        for (auto i = 0; i < minSize; ++i) {
            auto c = strs[0][i];
            for (auto &str : strs) {
                if (str[i] != c) {
                    return string(strs[0].cbegin(), strs[0].cbegin() + i);
                }
            }
        }
        return string(strs[0].cbegin(), strs[0].cbegin() + minSize);
    }
};

int main(int argc, char *argv[]) {
    Solution solution;
    vector<string> strs {"flower", "flow", "flight"};

    auto start = chrono::high_resolution_clock::now();
    auto result = solution.longestCommonPrefix(strs);
    auto end = chrono::high_resolution_clock::now();

    cout << result;
    cout << "\nin " << chrono::duration<float, milli>(end - start).count() << " ms." << endl;

    return 0;
}
