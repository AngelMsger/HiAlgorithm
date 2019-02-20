#include "list.h"

using namespace std;
using namespace angelmsger;

int main(int argc, char *argv[]) {
    List<int> list{5, 4, 1, 1, 3, 2};
    auto echo_int = echo<int>;
    list.traverse(echo_int);
    cout << "\nsize(): " << list.size() << "\nempty(): " << list.empty()
         << "\nget(1): " << list.get(1) << "\nput(1, -1)...\n";
    list.put(1, -1);
    list.traverse(echo_int);
    cout << "\ninsert(1, -2)...\n";
    list.insert(1, -2);
    list.traverse(echo_int);
    cout << "\nerase(1)....\n";
    list.erase(1);
    list.traverse(echo_int);
    cout << "\nfind(3): " << list.find(3)
         << "\ndisordered(): " << list.disordered()
         << "\ndeduplicated(): " << list.deduplicated() << '\n';
    list.traverse(echo_int);
    cout << "\ninsert(0, 1); insert(2, 2)...\n";
    list.insert(0, 1);
    list.insert(2, 2);
    list.traverse(echo_int);
    cout << "\nsort()...\n";
    list.sort();
    list.traverse(echo_int);
    cout << "\nremove(2)...\n";
    list.remove(2);
    list.traverse(echo_int);
    cout << "\nuniquify()...\n";
    list.uniquify();
    list.traverse(echo_int);
    cout << endl;
    return 0;
}
