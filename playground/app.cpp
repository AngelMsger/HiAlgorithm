#include <iostream>
#include <bitset>

using namespace std;

constexpr int M = 16 + 1;
constexpr int N = 16 + 1;

void update(int map[M][N], int i, int j) {
    if (i > 0 && j >= 0 && map[i - 1][j] != map[i][j] && map[i - 1][j] != 0) {
        map[i - 1][j] = map[i][j];
        update(map, i - 1, j);
    }
    if (i >= 0 && j > 0 && map[i][j - 1] != map[i][j] && map[i][j - 1] != 0) {
        map[i][j - 1] = map[i][j];
        update(map, i, j - 1);
    }
}

int main() {
    int map[M][N];
    memset(map, 0, M * N * sizeof(int));
    int m, n, v;

    cin >> m >> n;
//    while (cin >> m >> n) {
        for (auto i = 1; i <= m; ++i)
            for (auto j = 1; j <= n; ++j) {
                cin >> v;
                map[i][j] = v ? 1 : 0;
            }
        auto next = 1;
        for (auto i = 1; i <= m; ++i) {
            for (auto j = 1; j <= n; ++j) {
                auto cur = map[i][j];
                if (cur != 0) {
                    auto left = map[i][j - 1];
                    auto top = map[i - 1][j];
                    if (left != 0) {
                        map[i][j] = left;
                    } else if (top != 0) {
                        map[i][j] = top;
                    } else {
                        map[i][j] = next++;
                    }
                    update(map, i, j);
                }
            }
        }
        bitset<M * N + 1> b;
        for (auto i = 1; i <= m; ++i) {
            for (auto j = 1; j <= n; ++j) {
                auto flag = map[i][j];
                if (flag != 0) {
                    b.set(flag);
                }
            }
        }
        cout << b.count() << endl;
//    }
    return 0;
}