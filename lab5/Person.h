#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

class Person {
    std::string name;
    int age;
public:
    Person() : name("Jane Doe"), age(-1) {}
    Person(const std::string s, const int a) : name(s), age(a) {}
    Person(const Person& p) : name(p.name), age(p.age) {}
    virtual ~Person() {}
    void setName(const std::string n) { name = n; }
    void setAge(const int a) { age = a; }
    std::string getName() const { return name; }
    int getAge() const  { return age; }
    virtual void Show() = 0;
};

#endif
