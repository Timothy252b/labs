#pragma once
#include <iostream>
#include <string>

class Person {
protected:
    std::string name;
    int age;
public:
    Person() : name("Jane Doe"), age(-1) {}
    Person(std::string n, int a) : name(n), age(a) {}
    Person(const Person& p) : name(p.name), age(p.age) {}
    virtual ~Person() {}
    Person& operator=(const Person& p){
        name = p.name;
        age = p.age;
        return *this;
    }
    void setName(const std::string n) {
        name = n;
    }
    std::string getName() {
        return name;
    }
    int getAge() {
        return age;
    }
    Person& operator++() {
        age += 1;
        return *this;
    }
    Person operator++(int) {
        Person tmp(*this);
        age += 1;
        return tmp;
    }
    virtual void print() const  {
        std::cout << name << " " << age << " " << std::endl;
    }
    friend std::ostream& operator<<(std::ostream& cout, const Person& p);
    friend std::istream& operator>>(std::istream& cin, Person& p);
};
