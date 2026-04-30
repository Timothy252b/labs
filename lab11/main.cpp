#include <iostream>
#include <list>
#include <queue>
#include <vector>
#include <algorithm>
#include <stdexcept>

template<typename T>
struct Pair {
    T first, second;
    Pair(T f = T(), T s = T()) : first(f), second(s) {}
    bool operator<(const Pair& other) const { return first + second < other.first + other.second; }
    bool operator>(const Pair& other) const { return first + second > other.first + other.second; }
    bool operator==(const Pair& other) const { return first == other.first && second == other.second; }
    friend std::ostream& operator<<(std::ostream& os, const Pair& p) {
        os << "(" << p.first << "," << p.second << ")"; return os;
    }
};

// Task 1
void task1() {
    std::list<double> lst = {1.5, 2.5, 3.5, 4.5, 5.5};
    std::cout << "Task1 Initial: ";
    for (double d : lst) std::cout << d << " "; std::cout << std::endl;

    double sum = 0;
    for (double d : lst) sum += d;
    double avg = sum / lst.size();
    lst.push_back(avg);
    std::cout << "After adding avg: ";
    for (double d : lst) std::cout << d << " "; std::cout << std::endl;

    std::list<double> toErase;
    for (double d : lst) if (d > 2.0 && d < 4.0) toErase.push_back(d);
    for (double d : toErase) lst.remove(d);
    std::cout << "After erasing (2,4): ";
    for (double d : lst) std::cout << d << " "; std::cout << std::endl;

    double minElem = *std::min_element(lst.begin(), lst.end());
    double maxElem = *std::max_element(lst.begin(), lst.end());
    double sumMinMax = minElem + maxElem;
    std::list<double> modified;
    for (double d : lst) modified.push_back(d + sumMinMax);
    lst = modified;
    std::cout << "After adding min+max: ";
    for (double d : lst) std::cout << d << " "; std::cout << "\n\n";
}

// Task 2
void task2() {
    std::list<Pair<int>> lst = {Pair<int>(1,2), Pair<int>(3,4), Pair<int>(5,6), Pair<int>(7,8), Pair<int>(9,10)};
    std::cout << "Task2 Initial: ";
    for (auto& p : lst) std::cout << p << " "; std::cout << std::endl;

    int sum = 0;
    for (auto& p : lst) sum += p.first + p.second;
    double avg = sum / (double)lst.size();
    lst.push_back(Pair<int>(avg, 0));
    std::cout << "After adding avg: ";
    for (auto& p : lst) std::cout << p << " "; std::cout << std::endl;

    int keyLow = 5, keyHigh = 15;
    lst.remove_if([keyLow, keyHigh](const Pair<int>& p) {
        int key = p.first + p.second;
        return key >= keyLow && key <= keyHigh;
    });
    std::cout << "After erasing keys [5,15]: ";
    for (auto& p : lst) std::cout << p << " "; std::cout << std::endl;

    if (!lst.empty()) {
        auto minIt = std::min_element(lst.begin(), lst.end());
        auto maxIt = std::max_element(lst.begin(), lst.end());
        int sumMinMax = (minIt->first + minIt->second) + (maxIt->first + maxIt->second);
        std::list<Pair<int>> modified;
        for (auto& p : lst) modified.push_back(Pair<int>(p.first + sumMinMax, p.second + sumMinMax));
        lst = modified;
        std::cout << "After adding min+max to each element: ";
        for (auto& p : lst) std::cout << p << " "; std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Task 3 Parameterized list
template<typename T>
class MyList {
    std::list<T> data;
public:
    MyList(std::initializer_list<T> init) : data(init) {}
    void addAvg() {
        T sum = T();
        for (const auto& elem : data) sum = sum + elem;
        T avg = sum / data.size();
        data.push_back(avg);
    }
    void eraseByKeyRange(const T& low, const T& high) {
        data.remove_if([low, high](const T& elem) { return elem >= low && elem <= high; });
    }
    void addMinMaxToEach() {
        if (data.empty()) return;
        T minElem = *std::min_element(data.begin(), data.end());
        T maxElem = *std::max_element(data.begin(), data.end());
        T sumMinMax = minElem + maxElem;
        std::list<T> modified;
        for (const auto& elem : data) modified.push_back(elem + sumMinMax);
        data = modified;
    }
    void print() const {
        for (const auto& elem : data) std::cout << elem << " ";
        std::cout << std::endl;
    }
};

void task3() {
    MyList<double> lst = {1.1, 2.2, 3.3, 4.4, 5.5};
    std::cout << "Task3 Initial: "; lst.print();
    lst.addAvg();
    std::cout << "After adding avg: "; lst.print();
    lst.eraseByKeyRange(2.0, 4.0);
    std::cout << "After erasing [2,4]: "; lst.print();
    lst.addMinMaxToEach();
    std::cout << "After adding min+max: "; lst.print();
    std::cout << std::endl;
}

// Task 4 Priority queue adapter
void task4() {
    std::priority_queue<Pair<int>, std::vector<Pair<int>>, std::greater<Pair<int>>> pq;
    std::vector<Pair<int>> initial = {Pair<int>(1,5), Pair<int>(2,3), Pair<int>(7,1), Pair<int>(4,4), Pair<int>(3,2)};
    for (auto& p : initial) pq.push(p);
    std::cout << "Task4 Initial priority queue (ordered by sum):\n";
    auto temp = pq;
    while (!temp.empty()) { std::cout << temp.top() << " "; temp.pop(); }
    std::cout << std::endl;

    int sum = 0;
    std::vector<Pair<int>> vec;
    temp = pq;
    while (!temp.empty()) { vec.push_back(temp.top()); temp.pop(); }
    for (auto& p : vec) sum += p.first + p.second;
    double avg = sum / (double)vec.size();
    pq.push(Pair<int>(avg, 0));
    std::cout << "After adding avg: ";
    temp = pq;
    while (!temp.empty()) { std::cout << temp.top() << " "; temp.pop(); }
    std::cout << std::endl;

    std::priority_queue<Pair<int>, std::vector<Pair<int>>, std::greater<Pair<int>>> filtered;
    int low = 6, high = 10;
    temp = pq;
    while (!temp.empty()) {
        Pair<int> p = temp.top(); temp.pop();
        int key = p.first + p.second;
        if (key < low || key > high) filtered.push(p);
    }
    pq = filtered;
    std::cout << "After erasing keys [6,10]: ";
    temp = pq;
    while (!temp.empty()) { std::cout << temp.top() << " "; temp.pop(); }
    std::cout << std::endl;

    if (!pq.empty()) {
        std::vector<Pair<int>> all;
        temp = pq;
        while (!temp.empty()) { all.push_back(temp.top()); temp.pop(); }
        auto minIt = std::min_element(all.begin(), all.end());
        auto maxIt = std::max_element(all.begin(), all.end());
        int sumMinMax = (minIt->first + minIt->second) + (maxIt->first + maxIt->second);
        std::priority_queue<Pair<int>, std::vector<Pair<int>>, std::greater<Pair<int>>> modified;
        for (auto& p : all) modified.push(Pair<int>(p.first + sumMinMax, p.second + sumMinMax));
        pq = modified;
        std::cout << "After adding min+max to each: ";
        temp = pq;
        while (!temp.empty()) { std::cout << temp.top() << " "; temp.pop(); }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Task 5 Parameterized class with priority queue adapter
template<typename T>
class MyPriorityQueue {
    std::priority_queue<Pair<T>, std::vector<Pair<T>>, std::greater<Pair<T>>> pq;
public:
    MyPriorityQueue(std::initializer_list<Pair<T>> init) {
        for (const auto& p : init) pq.push(p);
    }
    void addAvg() {
        std::vector<Pair<T>> vec;
        auto temp = pq;
        T sum = T();
        while (!temp.empty()) { vec.push_back(temp.top()); temp.pop(); }
        for (const auto& p : vec) sum = sum + p.first + p.second;
        T avg = sum / vec.size();
        pq.push(Pair<T>(avg, T()));
    }
    void eraseByKeyRange(const T& low, const T& high) {
        std::priority_queue<Pair<T>, std::vector<Pair<T>>, std::greater<Pair<T>>> filtered;
        auto temp = pq;
        while (!temp.empty()) {
            Pair<T> p = temp.top(); temp.pop();
            T key = p.first + p.second;
            if (key < low || key > high) filtered.push(p);
        }
        pq = filtered;
    }
    void addMinMaxToEach() {
        if (pq.empty()) return;
        std::vector<Pair<T>> vec;
        auto temp = pq;
        while (!temp.empty()) { vec.push_back(temp.top()); temp.pop(); }
        auto minIt = std::min_element(vec.begin(), vec.end());
        auto maxIt = std::max_element(vec.begin(), vec.end());
        T sumMinMax = (minIt->first + minIt->second) + (maxIt->first + maxIt->second);
        std::priority_queue<Pair<T>, std::vector<Pair<T>>, std::greater<Pair<T>>> modified;
        for (const auto& p : vec) modified.push(Pair<T>(p.first + sumMinMax, p.second + sumMinMax));
        pq = modified;
    }
    void print() const {
        auto temp = pq;
        while (!temp.empty()) { std::cout << temp.top() << " "; temp.pop(); }
        std::cout << std::endl;
    }
};

void task5() {
    MyPriorityQueue<int> mpq = {{1,5}, {2,3}, {7,1}, {4,4}, {3,2}};
    std::cout << "Task5 Initial: "; mpq.print();
    mpq.addAvg();
    std::cout << "After adding avg: "; mpq.print();
    mpq.eraseByKeyRange(6, 10);
    std::cout << "After erasing keys [6,10]: "; mpq.print();
    mpq.addMinMaxToEach();
    std::cout << "After adding min+max: "; mpq.print();
}

int main() {
    task1();
    task2();
    task3();
    task4();
    task5();
    return 0;
}
