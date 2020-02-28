/**
 * 338 - 比特位计数
 * 给定一个非负整数 num。对于 0 ≤ i ≤ num 范围中的每个数字 i ，计算其二进制数中的 1 的数目并将它们作为数组返回。
 *
 * 示例 1:
 *
 * 输入: 2
 * 输出: [0,1,1]
 * 示例 2:
 *
 * 输入: 5
 * 输出: [0,1,1,2,1,2]
 */

#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

static auto _ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> result(num + 1);
        result[0] = 0;
        for (auto i = 1; i <= num; ++i) {
            result[i] = result[i >> 1] + (i & 1);
        }
        return result;
    }
};

int main() {
    Solution solution;
    auto result = solution.countBits(5);
    copy(result.cbegin(), result.cend(), ostream_iterator<int>(cout, ", "));
    cout << endl;
    return 0;
}