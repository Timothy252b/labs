#pragma once
#include <iostream>
#include <cstdio>
template<class T1, class T2>
class Pair {
    T1 first;
    T2 second;
public:
    Pair() : first(0), second(0) {}
    Pair(T1 f, T2 s) : first(f), second(s) {}
    template<class s1, class s2>
    Pair(const Pair<s1, s2>& p) : first(static_cast<T1>(p.getFirst())), second(static_cast<T2>(p.getSecond())) {}
    ~Pair() {}
    void setFirst(const T1 f) { first = f; }
    void setSecond(const T2 s) { second = s; }
    T1 getFirst() const { return first; }
    T2 getSecond() const { return second; }
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
    friend std::ostream& operator<<(std::ostream& cout, const Pair& p) {
        return cout << p.getFirst() << ":" << p.getSecond();
    }
    friend std::istream& operator>>(std::istream& cin, Pair& p) {
        std::cout << "Enter first: ";
        cin >> p.first;
        std::cout << "Enter second: ";
        cin >> p.second;
        return cin;
    }

};
