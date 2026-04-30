#include "Pair.h"
#include <iostream>
int main() {
    Pair one;
    Pair two(1, 1);
    Pair three(two);
    std::cout << one << " " << two << " " << three << std::endl;
    Pair four(2, 2.5);
    one = two = four;
    std::cout << one << " " << two << " " << three << " " << four << std::endl;
    one = one + 1;
    two = two + 2.5;
    std::cout << one << " " << two << std::endl;
    four = one - two;
    std::cout << four << std::endl;
    std::cin >> four >> one;
    std::cout << four << one;
    std::cout << std::endl;
    return 0;
}
