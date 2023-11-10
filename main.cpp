#include <iostream>
#include "n_real.h"
#include "n_array.h"

int main() {
    naive::real x = 3.12, y = 9.31;
    auto z = ++x;
    std::cout << z << '\n';
    std::cout << x << '\n';
}