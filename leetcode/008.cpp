/**
 * 008 - 字符串转整数 (atoi)
 * @see https://leetcode-cn.com/problems/string-to-integer-atoi/description/
 *
 * 实现 atoi，将字符串转为整数。
 *
 * 在找到第一个非空字符之前，需要移除掉字符串中的空格字符。如果第一个非空字符是正号或负号，选取该符号，并将其与后面尽
 * 可能多的连续的数字组合起来，这部分字符即为整数的值。如果第一个非空字符是数字，则直接将其与之后连续的数字字符组合起
 * 来，形成整数。
 *
 * 字符串可以在形成整数的字符后面包括多余的字符，这些字符可以被忽略，它们对于函数没有影响。
 *
 * 当字符串中的第一个非空字符序列不是个有效的整数；或字符串为空；或字符串仅包含空白字符时，则不进行转换。
 *
 * 若函数不能执行有效的转换，返回 0。
 *
 * 说明：
 * 假设我们的环境只能存储 32 位有符号整数，其数值范围是 [−231,  231 −
 * 1]。如果数值超过可表示的范围，则返回 INT_MAX (231 − 1) 或 INT_MIN (−231) 。
 *
 * 示例 1:
 * 输入: "42"
 * 输出: 42
 *
 * 示例 2:
 * 输入: "   -42"
 * 输出: -42
 *
 * 解释: 第一个非空白字符为 '-',
 * 它是一个负号。我们尽可能将负号与后面所有连续出现的数字组合起来，最后得到 -42
 * 。
 *
 * 示例 3:
 * 输入: "4193 with words"
 * 输出: 4193
 *
 * 解释: 转换截止于数字 '3' ，因为它的下一个字符不为数字。
 *
 * 示例 4:
 * 输入: "words and 987"
 * 输出: 0
 *
 * 解释: 第一个非空字符是 'w', 但它不是数字或正、负号。因此无法执行有效的转换。
 *
 * 示例 5:
 * 输入: "-91283472332"
 * 输出: -2147483648
 *
 * 解释: 数字 "-91283472332" 超过 32 位有符号整数范围。因此返回 INT_MIN (−231)
 * 。
 *
 * 解题思路:
 * 如解答，避免使用如long类型的变量来绕过int值的边界问题。
 */

#include <iostream>
#include <string>
#include <chrono>

using namespace std;

static auto _ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
   public:
    int myAtoi(string str) {
        // Many solution use long to avoid value overflow, in fact, however,
        // it's not allowed in the mean of this question.
        const auto length = str.size();
        const auto threshold = INT32_MAX / 10;
        const auto thresholdX10 = threshold * 10;
        auto i = str.find_first_not_of(' ');
        if (i >= length) return 0;
        auto indicator = 1;
        if (str[i] == '-' || str[i] == '+') {
            indicator = str[i] == '-' ? -1 : 1;
            ++i;
        }
        auto result = 0;
        while (i < length && '0' <= str[i] && str[i] <= '9') {
            if (result < threshold)
                result = result * 10 + (str[i++] - '0');
            else if (result == threshold) {
                auto candidate = str[i] - '0';
                auto limit = INT32_MAX - thresholdX10;
                if (indicator == 1) {
                    return candidate <= limit ? thresholdX10 + candidate
                                              : INT32_MAX;
                } else {
                    return candidate <= limit + 1
                               ? thresholdX10 * -1 - candidate
                               : INT32_MIN;
                }
            } else
                return indicator == 1 ? INT32_MAX : INT32_MIN;
        }
        return indicator * result;
    }
};

int main(int argc, char *argv[]) {
    Solution solution;

    auto start = chrono::high_resolution_clock::now();
    auto result1 = solution.myAtoi("-91283472332");
    auto result2 = solution.myAtoi("2147483646");
    auto result3 = solution.myAtoi("-2147483647");
    auto end = chrono::high_resolution_clock::now();

    cout << result1 << ", " << result2 << ", " << result3;
    cout << "\nin " << chrono::duration<float, milli>(end - start).count()
         << " ms." << endl;

    return 0;
}
