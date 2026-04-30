#include "Person.h"

std::ostream& operator<<(std::ostream& cout, const Person& p) {
    std::cout << "|Name: " << p.name << ", Age: " << p.age << "| ";
    return cout;
}
std::istream& operator>>(std::istream& cin, Person& p) {
    std::cout << "Enter name: ";
    std::getline(cin, p.name);
    std::cout << "Enter age: ";
    cin >> p.age;
    return cin;
}

