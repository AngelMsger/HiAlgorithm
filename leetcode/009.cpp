/**
 * 009 - 回文数
 * @see https://leetcode-cn.com/problems/palindrome-number/description/
 *
 * 判断一个整数是否是回文数。回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。
 *
 * 示例 1:
 * 输入: 121
 * 输出: true
 *
 * 示例 2:
 * 输入: -121
 * 输出: false
 * 解释: 从左向右读, 为 -121 。 从右向左读, 为 121- 。因此它不是一个回文数。
 *
 * 示例 3:
 * 输入: 10
 * 输出: false
 * 解释: 从右向左读, 为 01 。因此它不是一个回文数。
 *
 * 进阶:
 * 你能不将整数转为字符串来解决这个问题吗？
 *
 * 解题思路:
 * 字符串版本可以双端为起点遍历，非字符串版本同样有多种实现方式，如007中的数字反转，
 * 或本题给出的逐位取数。
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>

using namespace std;

static auto _ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
   private:
    bool stringVersion(int x) {
        auto xStr = to_string(x);
        auto front = xStr.cbegin(), back = xStr.cend() - 1;
        while (front < back && *front == *back) {
            front++;
            back--;
        }
        return front >= back;
    }

    bool nonStringVersion(int x) {
        if (x <= 0) {
            return !x;
        }
        vector<int> digits;
        auto digitsCount = static_cast<int>(log10(x)) + 1;
        for (auto i = 0; i < digitsCount; ++i) {
            digits.push_back(x % 10);
            x /= 10;
        }
        auto front = digits.cbegin(), back = digits.cend() - 1;
        while (front < back && *front == *back) {
            front++;
            back--;
        }
        return front >= back;
    }

   public:
    bool isPalindrome(int x) { return nonStringVersion(x); }
};

int main(int argc, char *argv[]) {
    Solution solution;

    auto start = chrono::high_resolution_clock::now();
    auto result = solution.isPalindrome(121);
    auto end = chrono::high_resolution_clock::now();

    cout << result;
    cout << "\nin " << chrono::duration<float, milli>(end - start).count()
         << " ms." << endl;

    return 0;
}
