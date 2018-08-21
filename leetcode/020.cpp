/**
 * 020 - 有效的括号
 * @see https://leetcode-cn.com/problems/valid-parentheses/description/
 *
 * 给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串，判断字符串是否有效。
 * 有效字符串需满足：
 * 左括号必须用相同类型的右括号闭合。
 * 左括号必须以正确的顺序闭合。
 * 注意空字符串可被认为是有效字符串。
 *
 * 示例 1:
 * 输入: "()"
 * 输出: true
 *
 * 示例 2:
 * 输入: "()[]{}"
 * 输出: true
 *
 * 示例 3:
 * 输入: "(]"
 * 输出: false
 *
 * 示例 4:
 * 输入: "([)]"
 * 输出: false
 *
 * 示例 5:
 * 输入: "{[]}"
 * 输出: true
 *
 * 解题思路：将扫描到的左括号入栈，右括号与栈顶元素比较，匹配则弹出相消，全部顺利匹配完成则返回真。
 */
#include <bits/stdc++.h>
using namespace std;

static auto _ = []() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    bool isValid(string s) {
        if (s.size() & 1 == 1) return false;
        unordered_set<char> lhs {'(', '[', '{'};
        unordered_map<char, char> rhs {{')', '('}, {']', '['}, {'}', '{'}};
        unordered_map<char, char>::const_iterator candidate;
        stack<char> history;
        for (const auto ch : s) {
            if (lhs.find(ch) != lhs.cend()) history.push(ch);
            else if ((candidate = rhs.find(ch)) != rhs.cend()) {
                if (history.empty() || history.top() != candidate->second) return false;
                else history.pop();
            }
        }
        return history.empty();
    }
};

int main(int argc, char *argv[]) {
    Solution solution;

    auto start = chrono::high_resolution_clock::now();
    auto result = solution.isValid("){");
    auto end = chrono::high_resolution_clock::now();

    cout << (result ? "matched" : "not matched") << endl;
    cout << "\nin " << chrono::duration<float, milli>(end - start).count() << " ms." << endl;

    return 0;
}
