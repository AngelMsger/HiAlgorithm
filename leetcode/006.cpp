/**
 * 006 - Z字形变换
 * @see https://leetcode-cn.com/problems/zigzag-conversion/description/
 *
 * 将字符串 "PAYPALISHIRING" 以Z字形排列成给定的行数：
 * P   A   H   N
 * A P L S I I G
 * Y   I   R
 * 之后从左往右，逐行读取字符："PAHNAPLSIIGYIR"
 * 实现一个将字符串进行指定行数变换的函数:
 * string convert(string s, int numRows);
 *
 * 示例 1:
 * 输入: s = "PAYPALISHIRING", numRows = 3
 * 输出: "PAHNAPLSIIGYIR"
 *
 * 示例 2:
 * 输入: s = "PAYPALISHIRING", numRows = 4
 * 输出: "PINALSIGYAHRPI"
 *
 * 解释:
 * P     I    N
 * A   L S  I G
 * Y A   H R
 * P     I
 *
 * 解题思路:
 * 按照规则逐步构造多个队列并顺序输出即可。
 */

#include <iostream>
#include <vector>
#include <sstream>
#include <chrono>

using namespace std;

static auto _ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
   public:
    string convert(string s, int numRows) {
        if (numRows < 2) {
            return s;
        }
        const auto length = s.size();
        auto bucketSize = numRows * 2 - 2;
        auto bucketsCount = length % bucketSize == 0 ? length / bucketSize
                                                     : length / bucketSize + 1;
        vector<vector<char>> rows((unsigned long)numRows);
        for (auto i = 0; i < bucketsCount; ++i) {
            auto j = 0, k = i * bucketSize;
            while (j < numRows && k < length) {
                rows[j].push_back(s[k]);
                ++j, ++k;
            }
            j -= 2;
            while (j > 0 && k < length) {
                rows[j].push_back(s[k]);
                --j, ++k;
            }
        }
        ostringstream oss;
        for (const vector<char> &row : rows) {
            copy(row.cbegin(), row.cend(), ostream_iterator<char>(oss));
        }
        return oss.str();
    }
};

int main(int argc, char *argv[]) {
    Solution solution;

    auto start = chrono::high_resolution_clock::now();
    auto result = solution.convert("", 6);
    auto end = chrono::high_resolution_clock::now();

    cout << result;
    cout << "\nin " << chrono::duration<float, milli>(end - start).count()
         << " ms." << endl;

    return 0;
}
