//
// Created by angelmsger on 8/13/18.
//
#include <bits/stdc++.h>
using namespace std;

/**
 * 007 - 反转整数
 * @see https://leetcode-cn.com/problems/reverse-integer/description/
 *
 * 给定一个 32 位有符号整数，将整数中的数字进行反转。
 *
 * 示例 1:
 * 输入: 123
 * 输出: 321
 *
 * 示例 2:
 * 输入: -123
 * 输出: -321
 *
 * 示例 3:
 * 输入: 120
 * 输出: 21
 *
 * 注意:
 * 假设我们的环境只能存储 32 位有符号整数，其数值范围是 [−231,  231 − 1]。根据这个假设，如果反转后的整数溢出，则返回 0。
 *
 * 解题思路：虽然是简单的问题，但要注意数值溢出以及除数为0的特殊情况。
 */

class Solution {
public:
    int reverse(int x) {
        const auto xDir = x >= 0 ? 1 : -1;
        auto result = 0;
        for(auto i = abs(x); i > 0; i /= 10) {
            auto candidate = result * 10 + (i % 10);
            if (candidate / 10 != result) {
                return 0;
            }
            result = candidate;
        }
        return result * xDir;
    }
};

int main(int argc, char *argv[]) {
    Solution solution;

    auto start = chrono::high_resolution_clock::now();
    auto result = solution.reverse(-123);
    auto end = chrono::high_resolution_clock::now();

    cout << result;
    cout << "\nin " << chrono::duration<float, milli>(end - start).count() << " ms." << endl;

    return 0;
}
