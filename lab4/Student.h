#include "Person.h"

class Student : public Person {
protected:
    std::string subject;
    int mark;
public:
    Student() : Person(), subject("Astrology"), mark(-1) {}
    Student(std::string n, int a, std::string s, int m)
        : Person(n, a), subject(s), mark(m) {}
    Student(const Student& s) 
        : Person(s.name, s.age), subject(s.subject), mark(s.mark) {}
    ~Student() {}
    Student& operator=(const Student& s) {
        name = s.name;
        age = s.age;
        subject = s.subject;
        mark = s.mark;
        return *this;
    }
    void setSubject(const std::string s) {
        subject = s;
    }
    void setMark(const int m) {
        mark = m;
    }
    friend std::ostream& operator<<(std::ostream& cout, const Student& s);
    friend std::istream& operator>>(std::istream& cin, Student& s);
    void print() const {
        Person::print();
        std::cout << subject << " " << mark << std::endl;
    }
    void aboutMark() {
        if (mark < 3) std::cout << "Very bad student, fired!" << std::endl;
    }
};
