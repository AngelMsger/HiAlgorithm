/**
 * 753 - 破解保险箱
 * @see https://leetcode-cn.com/problems/cracking-the-safe/
 *
 * 有一个需要密码才能打开的保险箱。密码是 n 位数, 密码的每一位是 k 位序列 0, 1, ..., k-1 中的一个。
 * 你可以随意输入密码，保险箱会自动记住最后 n 位输入，如果匹配，则能够打开保险箱。
 * 举个例子，假设密码是 "345"，你可以输入 "012345" 来打开它，只是你输入了 6 个字符。
 * 请返回一个能打开保险箱的最短字符串。
 *
 * 示例1:
 * 输入: n = 1, k = 2
 * 输出: "01"
 * 说明: "10"也可以打开保险箱。
 *
 * 示例2:
 * 输入: n = 2, k = 2
 * 输出: "00110"
 * 说明: "01100", "10011", "11001" 也能打开保险箱。
 *
 * 提示：
 * n 的范围是 [1, 4]。
 * k 的范围是 [1, 10]。
 * k^n 最大可能为 4096。
 *
 * 解题思路:
 * 易知可能的排列总数，希望每一个排列能够尽可能复用前一个排列的后缀。
 * 每次复用上一个密码的 n - 1 位作为前缀进行 DFS，会在较少的回溯后找到这样的序列。
 * 数学上相关概念为：De Bruijn sequence。
 */

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <chrono>

using namespace std;

static auto _ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
private:
    unordered_set<string> visited;
    vector<char> result;
public:
    bool dfs(const string &shard, const int k, const int target) {
        if (visited.size() == target) return true;
        for (auto i = 0; i < k; ++i) {
            auto digit = (char)('0' + i);
            auto val = shard + digit;
            if (visited.find(val) == visited.cend()) {
                visited.insert(val);
                result.push_back(digit);
                if (dfs(val.substr(1), k, target)) return true;
                else {
                    result.pop_back();
                    visited.erase(val);
                }
            }
        }
        return false;
    }

    string crackSafe(int n, int k) {
        visited.clear();
        result.clear();

        for (auto i = 0; i < n; ++i) result.push_back('0');
        visited.insert(string(n, '0'));

        dfs(string(n - 1, '0'), k, pow(k, n));

        result.push_back(0);
        return string(result.data());
    }
};

int main() {
    Solution solution;

    auto start = chrono::high_resolution_clock::now();
    auto result = solution.crackSafe(2, 2);
    auto end = chrono::high_resolution_clock::now();

    cout << result;
    cout << "\nin " << chrono::duration<float, milli>(end - start).count()
         << " ms." << endl;
}