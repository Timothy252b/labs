#pragma once
#include <iostream>
#include <string>

class Salary {
    std::string name;
    double salary;
    int bonusPercent;
public:
    Salary() : name("empty"), salary(0.0), bonusPercent(0) {}
    
    Salary(const std::string& n, double s, int bP)  // const reference для эффективности
        : name(n), salary(s), bonusPercent(bP) {}
    
    Salary(const Salary& s) = default;  // Можно использовать default
    
    ~Salary() = default;
    
    void setSalary(double s) { salary = s; }
    void setBonus(int b) { bonusPercent = b; }
    
    const std::string& getName() const { return name; }  // const методы
    double getSalary() const { return salary; }
    int getBonus() const { return bonusPercent; }
    
    void print() const {
        std::cout << name << " " << salary << " " << bonusPercent << std::endl;
    }
};
