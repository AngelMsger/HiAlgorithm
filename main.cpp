// Entrance of Program.

#include <iostream>
#include <chrono>
#include <iterator>
#include "leetcode.h"

using namespace std;

int main() {
    Solution solution;
    vector<int> testCase = {-1, 0, 1, 2, -1, 4};
    ostream_iterator<int, char> osIterator(cout, ",");
    auto start = chrono::high_resolution_clock::now();
    // Answer should be [[-1,-1,2],[-1,0,1]]
    auto answer = solution.threeSum(testCase);
    auto end = chrono::high_resolution_clock::now();
    for (auto x: answer) {
        cout << '[';
        copy(x.begin(), x.end(), osIterator);
        cout << "],\n";
    }
    cout << chrono::duration<float, milli>(end - start).count() << endl;
    return 0;
}
