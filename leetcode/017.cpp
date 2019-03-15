/**
 * 017 - 电话号码的字母组合
 * @see
 * https://leetcode-cn.com/problems/letter-combinations-of-a-phone-number/description/
 *
 * 给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。
 * 给出数字到字母的映射与T9电话按键相同。注意 1 不对应任何字母。
 *
 * 示例:
 * 输入："23"
 * 输出：["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
 *
 * 说明:
 * 尽管上面的答案是按字典序排列的，但是你可以任意选择答案输出的顺序。
 *
 * 解题思路:
 * 以树的结构思考问题。
 */

#include <iostream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

static auto _ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

static const vector<string> T = {"",    "",    "abc",  "def", "ghi",
                                 "jkl", "mno", "pqrs", "tuv", "wxyz"};

class Solution {
   private:
    void doCombinations(const string &digits, vector<string> &result,
                        const int level = 0, const string &prefix = "") {
        if (level == digits.size())
            result.emplace_back(prefix);
        else if ('0' <= digits[level] && digits[level] <= '9') {
            for (auto ch : T[digits[level] - '0']) {
                doCombinations(digits, result, level + 1, prefix + ch);
            }
        }
    }

   public:
    vector<string> letterCombinations(string digits) {
        vector<string> result;
        if (digits.empty()) return result;
        doCombinations(digits, result);
        return result;
    }
};

int main(int argc, char *argv[]) {
    Solution solution;

    auto start = chrono::high_resolution_clock::now();
    auto result = solution.letterCombinations("23");
    auto end = chrono::high_resolution_clock::now();

    copy(result.cbegin(), result.cend(), ostream_iterator<string>(cout, ","));
    cout << "\nin " << chrono::duration<float, milli>(end - start).count()
         << " ms." << endl;

    return 0;
}
