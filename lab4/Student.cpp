#include "Student.h"

std::ostream& operator<<(std::ostream& cout, const Student& s) {
    cout << "|Student: ";
    const Person* p = &s;
    cout << *p;
    cout << "Subject: "  << s.subject << ", Mark:" << s.mark << " |"; 
    return cout;
}
std::istream& operator>>(std::istream& cin, Student& s) {
    std::cout << "Enter student:" << std::endl;
    Person& p = s;
    cin >> p;
    cin.ignore();
    std::cout << "Subject: ";
    std::getline(std::cin, s.subject);
    std::cout << "Mark: ";
    cin >> s.mark;
    return cin;
}
