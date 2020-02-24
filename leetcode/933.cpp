#include <iostream>
#include <queue>

using namespace std;

static auto _ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class RecentCounter {
protected:
    int q[10000];
    int *front, *back;
public:
    RecentCounter() {
        this->back = this->front = q;
    }

    int ping(int t) {
        while (
            this->back != this->front &&
            t - *(this->front) > 3000
        ) ++this->front;
        *(this->back++) = t;
        return this->back - this->front;
    }
};

int main() {
    RecentCounter counter;
    int timestamps[]{1, 100, 3001, 3002};
    for (int timestamp : timestamps) {
        cout << counter.ping(timestamp) << '\n';
    }
    cout << endl;
    return 0;
}
