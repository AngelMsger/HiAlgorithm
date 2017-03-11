// Entrance of Program.

#include <iostream>
#include <chrono>

using namespace std;

int main() {
    auto start = chrono::high_resolution_clock::now();
    cout << "Nothing Here!" << endl;
    auto end = chrono::high_resolution_clock::now();
    cout << chrono::duration<float, milli>(end - start).count() << endl;
    return 0;
}
