/**
 * 032 - 最长有效括号
 * @see https://leetcode-cn.com/problems/longest-valid-parentheses/
 *
 * 给定一个只包含 '(' 和 ')' 的字符串，找出最长的包含有效括号的子串的长度。
 *
 * 示例 1:
 * 输入: "(()"
 * 输出: 2
 * 解释: 最长有效括号子串为 "()"
 *
 * 示例 2:
 * 输入: ")()())"
 * 输出: 4
 * 解释: 最长有效括号子串为 "()()"
 *
 * 解题思路:
 */

#include <cmath>
#include <iostream>
#include <stack>
#include <string>

using namespace std;

static auto _ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
   public:
    int longestValidParentheses(string s) {
        unsigned int head = 0, max_length = 0;
        stack<char> memo;
        for (auto i = 0; i < s.size(); ++i) {
            auto c = s[i];
            if (c == '(') {
                memo.push(c);
            } else if (c == ')' && !memo.empty() && memo.top() == '(') {
                memo.pop();
                max_length = max(max_length, i - head);
            } else {
                head = i + 1;
            }
        }
        return max_length;
    }
};

int main(int argc, char *argv[]) {
    Solution solution;
    auto test_case_1 = "(()";
    auto test_case_2 = ")()())";
    cout << solution.longestValidParentheses(test_case_1) << ", "
         << solution.longestValidParentheses(test_case_2) << endl;
}
