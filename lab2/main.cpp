#include "Salary.h"

int main() {
    Salary s;
    Salary t("Ivan", 888888, 1);
    Salary u(t);
    std::cout << "s: " << std::endl;
    s.print();
    s.setSalary(1616);
    std::cout << "s: " << std::endl;
    s.print();
    std::cout << "t: " << std::endl;
    t.print();
    std::cout << "u: " << std::endl;
    u.print();
    return 0;
}

