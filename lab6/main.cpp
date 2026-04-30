#include "List.h"
#include "ListIter.h"

int main() {
    List l1;
    List l2(3);
    l1.pushBack(1);
    l1.pushBack(2);
    l1.pushBack(3);
    l2[0] = 1;
    l2[1] = 2;
    l2[2] = 3;
    List l3 = l1*l2;
    ListIter li(l3);
    for (int i = 0; i < 3; i++) {
        std::cout << *li << std::endl;
        li = li+1;
    }
    return 0;
}
