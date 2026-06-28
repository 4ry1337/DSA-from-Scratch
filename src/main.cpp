#include "list.h"
#include <iostream>

int main() {
    dsa::List<int> list;
    std::cout << sizeof(list);
    list.push_back(12);
    list.push_back(13);
    list.push_back(145);
    return 0;
}
