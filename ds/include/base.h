#ifndef HIALGORITHM_BASE_H
#define HIALGORITHM_BASE_H

#include <cmath>
#include <ctime>
#include <iostream>
#include <random>

using namespace std;

static auto _ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

default_random_engine *get_engine() noexcept {
    try {
        static default_random_engine engine(
            static_cast<unsigned int>(time(nullptr)));
        return &engine;
    } catch (...) {
        return nullptr;
    }
}

inline size_t rand_int(size_t lo, size_t hi) {
    assert(lo < hi);
    auto engine = get_engine();
    if (engine) {
        uniform_int_distribution<size_t> distribution(lo, hi - 1);
        return distribution(*engine);
    } else {
        return lo + (hi - lo) / 2;
    }
}

template <typename T>
void echo(const T &val) { cout << val << ", "; };

template <typename K, typename V>
void echo(const K &key, const V &val) { cout << '(' << key << ", " << val << "), "; };

#endif  // HIALGORITHM_BASE_H
