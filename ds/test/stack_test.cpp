#include "stack.h"

using namespace angelmsger;

int main(const int argc, const char *argv[]) {
    Stack<int> stack;
    cout << "push()...\n";
    for (auto i = 0; i < 4; ++i) stack.push(i);
    cout << "top(): " << stack.top() << '\n';
    while (!stack.empty()) cout << "pop(): " << stack.pop() << '\n';
    cout << "size(): " << stack.size() << endl;
    return 0;
}
