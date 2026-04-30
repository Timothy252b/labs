#include "Person.h"

class Student : public Person {
    std::string subject;
    int mark;
public:
    Student() : Person(), subject("Astrology"), mark(-1) {}
    Student(std::string n, int a, std::string s, int m)
        : Person(n, a), subject(s), mark(m) {}
    Student(const Student& s) : Person(s), subject(s.subject), mark(s.mark) {}
    ~Student() {}
    void Show() override {
        Person::Show();
        std::cout << "subject: " << subject << std::endl;
        std::cout << "mark: " << mark << std::endl;
    }
    friend std::ostream& operator<<(std::ostream& cout, const Student& s);
    friend std::istream& operator>>(std::istream& cim, Student& s);
    void setSubject(const std::string s) {
        subject = s;
    }
    void setMark(const int m) {
        mark = m;
    }
    std::string getSubject() const {
        return subject;
    }
    int getMark() const {
        return mark;
    }
    void isGood() const {
        if (mark < 3) std::cout << "bad student!" << std::endl;
        else std::cout << "good student!" << std::endl;
    }
};
