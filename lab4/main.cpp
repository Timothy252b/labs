#include "Student.h"
//#include "Person.h"

int main() {
    Student s;
    Person p;
    const Person* ps = &s;
    std::cout << p << std::endl;
    std::cout << s << std::endl;
    std::cout << *ps << std::endl;
    Student t;
    std::cin >> t;
    std::cout << t << std::endl;
    Student* pss = &t;
    pss->aboutMark();
    Person* pp = &p;
    pp->print();
    pp = &t;
    pp->print();
    return 0;
}
