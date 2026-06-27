#include "vector.h"
#include <iostream>

int main() {
    // dsa::List<int> a{};
    dsa::Vector<int> a;
    for (int i = 0; i < 10; ++i) {
        a.push_back(i);
    }
    for (auto x : a) {
        std::cout << x << "\n";
    }
    std::cout << std::endl;
    return 0;
}
