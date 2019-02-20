#include "bs_tree.h"

using namespace angelmsger;

int main(const int argc, const char *argv[]) {
    BSTree<int, char> tree;
    auto echo_pair = echo<int, char>;
    cout << "\ntree.size(): " << tree.size()
         << "\ntree.height(): " << tree.height()
         << "\ntree.empty(): " << (tree.empty() ? "true" : "false");
    cout << "\ntree.set(3, 'd'), ..., tree.set(6, 'g')...\n";
    tree.set(3, 'd');
    tree.set(1, 'b');
    tree.set(0, 'a');
    tree.set(2, 'c');
    tree.set(5, 'f');
    tree.set(4, 'e');
    tree.set(6, 'g');
    auto result = tree.get(6);
    cout << "tree.get(6): ";
    if (result) cout << *result;
    else cout << "NULL";
    cout << "\ntree.size(): " << tree.size()
         << "\ntree.height(): " << tree.height()
         << "\ntree.empty(): " << (tree.empty() ? "true" : "false")
         << "\ntree.traverse_bfs(): ";
    tree.traverse_bfs(echo_pair);
    cout << "\ntree.traverse_dfs_prev(): ";
    tree.traverse_dfs_prev(echo_pair);
    cout << "\ntree.traverse_dfs_in(): ";
    tree.traverse_dfs_in(echo_pair);
    cout << "\ntree.traverse_dfs_post(): ";
    tree.traverse_dfs_post(echo_pair);
    tree.remove(3);
    cout << "\ntree.remove(3): ";
    tree.traverse_dfs_in(echo_pair);
    tree.remove(0);
    cout << "\ntree.remove(0): ";
    tree.traverse_dfs_in(echo_pair);
    cout << "\ntree.size(): " << tree.size()
         << "\ntree.height(): " << tree.height()
         << "\ntree.empty(): " << (tree.empty() ? "true" : "false")
         << endl;
    return 0;
}
