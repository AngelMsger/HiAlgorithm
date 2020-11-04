#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

static auto _ = []() {
   ios::sync_with_stdio(false);
   cin.tie(nullptr);
   return nullptr;
}();

class Solution {
public:
    int evalRPN(const vector<string>& tokens) {
        stack<int> history;
        for (const auto & token : tokens) {
            if (token == "+") {
                auto rhs = history.top(); history.pop();
                auto lhs = history.top(); history.pop();
                history.push(lhs + rhs);
            } else if (token == "-") {
                auto rhs = history.top(); history.pop();
                auto lhs = history.top(); history.pop();
                history.push(lhs - rhs);
            } else if (token == "*") {
                auto rhs = history.top(); history.pop();
                auto lhs = history.top(); history.pop();
                history.push(lhs * rhs);
            } else if (token == "/") {
                auto rhs = history.top(); history.pop();
                auto lhs = history.top(); history.pop();
                history.push(lhs / rhs);
            } else {
                history.push(stod(token));
            }
        }
        return history.top();
    }
};

int main() {
    Solution solution;
    auto result = solution.evalRPN({
        // (6 / ((9 + 3) * -11)) * 10 + 17 + 5
        "10","6","9","3","+","-11","*","/","*","17","+","5","+"
    });
    cout << result << endl;
    return 0;
}