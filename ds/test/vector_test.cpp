#include "vector.h"

using namespace std;
using namespace angelmsger;

int main(int argc, char *argv[]) {
    Vector<int> vec{5, 4, 1, 1, 3, 2};
    auto echo_int = echo<int>;
    vec.traverse(echo_int);
    cout << "\nsize(): " << vec.size() << "\nempty(): " << vec.empty()
         << "\nget(1): " << vec.get(1) << "\nput(1, -1)...\n";
    vec.put(1, -1);
    vec.traverse(echo_int);
    cout << "\ninsert(1, -2)...\n";
    vec.insert(1, -2);
    vec.traverse(echo_int);
    cout << "\nerase(1)....\n";
    vec.erase(1);
    vec.traverse(echo_int);
    cout << "\nfind(3): " << vec.find(3) << "\nsearch(3): " << vec.search(3)
         << "\ndisordered(): " << vec.disordered()
         << "\ndeduplicated(): " << vec.deduplicated() << '\n';
    vec.traverse(echo_int);
    cout << "\ninsert(0, 1); insert(2, 2)...\n";
    vec.insert(0, 1);
    vec.insert(2, 2);
    vec.traverse(echo_int);
    cout << "\nsort()...\n";
    vec.sort();
    vec.traverse(echo_int);
    cout << "\nremove(2)...\n";
    vec.remove(2);
    vec.traverse(echo_int);
    cout << "\nuniquify()...\n";
    vec.uniquify();
    vec.traverse(echo_int);
    cout << endl;
    return 0;
}
