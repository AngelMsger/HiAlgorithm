/**
 * TODO: Unfinished Solution.
 * 028 - 实现strStr()
 * @see https://leetcode-cn.com/problems/implement-strstr/description/
 *
 * 实现 strStr() 函数。
 * 给定一个 haystack 字符串和一个 needle 字符串，在 haystack 字符串中找出 needle
 * 字符串出现的 第一个位置 (从0开始)。如果不存在，则返回  -1。
 *
 * 示例 1:
 * 输入: haystack = "hello", needle = "ll"
 * 输出: 2
 *
 * 示例 2:
 * 输入: haystack = "aaaaa", needle = "bba"
 * 输出: -1
 *
 * 说明:
 * 当 needle 是空字符串时，我们应当返回什么值呢？这是一个在面试中很好的问题。
 * 对于本题而言，当 needle 是空字符串时我们应当返回 0 。这与C语言的 strstr()
 * 以及 Java的 indexOf() 定义相符。
 *
 * 解题思路:
 * 最直接的思路是暴力匹配，但根据此前做题的经验和对此过程的分析不难发现，这种做法实际上存在重复
 * 可优化的过程(前面有一部分已经成功匹配了，但这一信息没有被后面的过程所利用)。对于字符串匹配问
 * 题，比较经典的算法是 KMP 算法。
 *
 * @see https://blog.csdn.net/v_july_v/article/details/7041827
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

// TODO: Unfinished Solution.
class Solution {
   private:
    int kmpSolution(const string &haystack, const string &needle) {
        vector<int> lps(needle.size(), 0);
        auto len = 0;
        for (auto i = 1; i < lps.size(); ++i) {
            if (needle[i] == needle[len]) {
                len++;
            } else {
                while (len > 0 && needle[len] == needle[i]) {
                    len = lps[len];
                }
            }
        }
        return 0;
    }

   public:
    int strStr(string haystack, string needle) {
        return kmpSolution(haystack, needle);
    }
};

int main(int argc, char *argv[]) {
    Solution solution;
    auto haystack = "hello", needle = "ll";

    auto start = chrono::high_resolution_clock::now();
    auto result = solution.strStr(haystack, needle);
    auto end = chrono::high_resolution_clock::now();

    cout << result;
    cout << "\nin " << chrono::duration<float, milli>(end - start).count()
         << " ms." << endl;

    return 0;
}
