/**
 * 091 - 解码方法
 *
 * 一条包含字母 A-Z 的消息通过以下方式进行了编码：
 *
 * 'A' -> 1
 * 'B' -> 2
 * ...
 * 'Z' -> 26
 * 给定一个只包含数字的非空字符串，请计算解码方法的总数。
 *
 * 示例 1:
 *
 * 输入: "12"
 * 输出: 2
 * 解释: 它可以解码为 "AB"（1 2）或者 "L"（12）。
 * 示例 2:
 *
 * 输入: "226"
 * 输出: 3
 * 解释: 它可以解码为 "BZ" (2 26), "VF" (22 6), 或者 "BBF" (2 2 6) 。
 *
 * 解题思路：
 * 求计数的划分型动态规划。
 * 最后一步：有效子母对应数字应在 1 - 26 之间，即有可能占 1 或 2 位。以字符串 "226"
 *         为例，最后一个子母有可能是 6，也有可能是 26。则整个字符串解码后的可能性为
 *         22 的可能性 + 2 的可能性。
 * 得到子结构：前 i 个字符解码可能性，当第 i 个字符本身可被解码时，即可包括前 i - 1
 *          个字符解码可能性，当第 i - 1 个字符和第 i 个字符合并后的数字可被解码
 *          时，即可包括前 i - 2 个字符解码可能性。
 * 得到递推式：decodingCounts[i] = decodingCounts[i - 2]    若最后一位有效
 *                              + decodingCounts[i - 1];  若最后两位有效
 * 临界条件：decodingCounts[0] = 1，计算 decodingCounts[i] 时，与
 *         decodingCounts[i - 1] 相加的前提条件为 s[i] 在 1 - 9 之间，与
 *         decodingCounts[i - 2] 相加的前提条件为 s[i - 1] * 10 + s[i]
 *         在 1 - 26 之间。
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
    int numDecodings(string s) {
        auto length = s.size();
        // 前 i 个字符的解码数量
        auto *decodingCounts = new int[length + 1];
        decodingCounts[0] = 1;
        for (auto i = 1; i <= length; ++i) {
            int charIndex;
            decodingCounts[i] = 0;
            charIndex = s[i - 1] - '0';
            if (1 <= charIndex && charIndex <= 9) {
                decodingCounts[i] += decodingCounts[i - 1];
            }
            if (2 <= i) {
                charIndex = (s[i - 2] - '0') * 10 + (s[i - 1] - '0');
                if (10 <= charIndex && charIndex <= 26) {
                    decodingCounts[i] += decodingCounts[i - 2];
                }
            }
        }
        auto count = decodingCounts[length];
        delete[] decodingCounts;
        return count;
    }
};

int main() {
    Solution solution;
    cout << solution.numDecodings("226") << '\n'
         << solution.numDecodings("01") << endl;
    return 0;
}