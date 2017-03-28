// Entrance of Program.

#include <iostream>
#include <chrono>
#include <iterator>
#include "solution.h"

using namespace std;

int main() {
    Solution solution;
    vector<int> testCase = {-1, 0, 1, 2, -1, 4};
    ostream_iterator<int, char> osIterator(cout, ",");
    auto start = chrono::high_resolution_clock::now();

    auto l1 = new ListNode(5);
    auto l2 = new ListNode(5);
    auto answer = solution.addTwoNumbers(l1, l2);

    // Test Problem 15, Answer should be [[-1,-1,2],[-1,0,1]]
    // auto answer = solution.threeSum(testCase);

    auto end = chrono::high_resolution_clock::now();
    // Test Problem 15, Answer should be [[-1,-1,2],[-1,0,1]]
    // for (auto x: answer) {
    //     cout << '[';
    //     copy(x.begin(), x.end(), osIterator);
    //     cout << "],\n";
    // }

    // Test Problem 2, Answer should be "01"
    for (; answer; answer = answer->next) {
        cout << answer->val;
    }
    cout << '\n';

    cout << chrono::duration<float, milli>(end - start).count() << endl;
    return 0;
}
