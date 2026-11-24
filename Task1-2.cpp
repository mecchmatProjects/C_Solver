#include <iostream>
#include <utility>

int sum_recursive(int n) {
    if (n <= 0) {
        return 0;
    }
    return n + sum_recursive(n - 1);
}

std::pair<int, int> f(int n) {
    static int calls = 0;
    ++calls;
    return {sum_recursive(n), calls};
}

int main() {
    int q = 0;
    if (!(std::cin >> q)) {
        return 0;
    }

    for (int i = 0; i < q; ++i) {
        int n = 0;
        std::cin >> n;
        auto [sum, calls] = f(n);
        std::cout << sum << ' ' << calls << '\n';
    }

    return 0;
}