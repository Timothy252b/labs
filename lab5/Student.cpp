#include "Student.h"

std::ostream& operator<<(std::ostream& cout, const Student& s) {
    cout << "name: " << s.getName() << std::endl;
    cout << "age: " << s.getAge() << std::endl;
    cout << "subject: " << s.getSubject() << std::endl;
    cout << "mark: " << s.getMark() << std::endl;
    return cout;
}
/*
std::istream& operator>>(std::istream& cin, Student& s) {
    std::cout << "enter name: ";
    s.setName();
    std::cout << "enter age: ";
    s.setAge();
    std::cout << "enter subject: ";
    s.setSubject();
    std::cout << "enter mark: ";
    s.setMark();
    return cin;
}
*/
