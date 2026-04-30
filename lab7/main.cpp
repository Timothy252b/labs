#include "List.h"
#include "Pair.h"

int main() {
    List<int> l1;
    List<float> l2(3);
    l1.pushBack(1);
    l1.pushBack(2);
    l1.pushBack(3);
    l2[0] = 1;
    l2[1] = 2;
    l2[2] = 3;
    List<double> l3(l2);
    List lres = l1 * l2 * l3;
    lres.print();
    Pair<int, double> a;
    Pair<double, int> b(1,2);
    Pair<float, int> c(b);
    std::cout << a << std::endl << b << std::endl << c << std::endl;
    return 0;
}
