#pragma once
#include <iostream>
#include <cstdio>

class Pair {
    int first;
    double second;
public:
    Pair() : first(0), second(0) {}
    Pair(int f, double s) : first(f), second(s) {}
    Pair(const Pair& p) : first(p.first), second(p.second) {}
    ~Pair() {}
    void setFirst(const int f) { first = f; }
    void setSecond(const double s) { second = s; }
    int getFirst() const { return first; }
    double getSecond() const { return second; }
    Pair& operator=(const Pair& p) {
        first = p.first;
        second = p.second;
        return *this;
    }
    Pair operator-(const Pair& p) const {
        Pair tmp(first-p.first, second-p.second);
        return tmp;
    }
    Pair operator+(const int f) const {
        return Pair(first+f, second);
    }
    Pair operator+(const double s) const {
        return Pair(first, second+s);
    }
    friend std::ostream& operator<<(std::ostream& cout, const Pair& p);
    friend std::istream& operator>>(std::istream& cin, Pair& p);
};
