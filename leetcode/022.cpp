/**
 * 022 - 括号生成
 * @see https://leetcode-cn.com/problems/generate-parentheses/description/
 *
 * 给出 n 代表生成括号的对数，请你写出一个函数，使其能够生成所有可能的并且有效的括号组合。
 * 例如，给出 n = 3，生成结果为：
 *
 * [
 *  "((()))",
 *  "(()())",
 *  "(())()",
 *  "()(())",
 *  "()()()"
 *  ]
 *
 * 解题思路：每放置一个左括号，就可以多放置一个右括号。
 */
#include <bits/stdc++.h>
using namespace std;

static auto _ = []() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
// TODO: 修正非线程安全写法。
private:
    int n = 0;
    vector<string> result;
    void backtrack(string &prefix, const int left, const int right) {
        if (prefix.size() == 2 * n) result.push_back(prefix);
        else {
            if (left < n) {
                prefix.push_back('(');
                backtrack(prefix, left + 1, right);
                prefix.pop_back();
            };
            if (right < left) {
                prefix.push_back(')');
                backtrack(prefix, left, right + 1);
                prefix.pop_back();
            };
        }
    }
public:
    vector<string> generateParenthesis(int n) {
        this->n = n;
        string prefix;
        backtrack(prefix, 0, 0);
        return this->result;
    }
};

int main(int argc, char *argv[]) {
    Solution solution;

    auto start = chrono::high_resolution_clock::now();
    auto result = solution.generateParenthesis(3);
    auto end = chrono::high_resolution_clock::now();

    auto console_iter = ostream_iterator<string>(cout, "\n");
    copy(result.cbegin(), result.cend(), console_iter);
    cout << "\nin " << chrono::duration<float, milli>(end - start).count() << " ms." << endl;

    return 0;
}
