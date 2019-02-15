#include "queue.h"

using namespace angelmsger;

int main(const int argc, const char *argv[]) {
    Queue<int> queue;
    cout << "push()...\n";
    for (auto i = 0; i < 4; ++i) queue.push(i);
    cout << "front(): " << queue.front() << "\nback():" << queue.back() << '\n';
    while (!queue.empty()) cout << "pop(): " << queue.pop() << '\n';
    cout << "size(): " << queue.size() << endl;
    return 0;
}
