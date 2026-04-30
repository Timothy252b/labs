#include <iostream>
#include <set>
#include <list>
#include <algorithm>
#include <numeric>
#include <vector>

class Pair {
public:
    int first;
    int second;

    Pair(int f = 0, int s = 0) : first(f), second(s) {}

    bool operator<(const Pair& other) const {
        if (first != other.first) return first < other.first;
        return second < other.second;
    }

    bool operator==(const Pair& other) const {
        return first == other.first && second == other.second;
    }

    friend std::ostream& operator<<(std::ostream& os, const Pair& p) {
        os << "(" << p.first << "," << p.second << ")";
        return os;
    }
};

void task1_addToMultiset(std::multiset<double>& ms, const std::vector<double>& values) {
    for (double val : values) ms.insert(val);
}

void task1_deleteElementsInRange(std::multiset<double>& ms, double low, double high) {
    auto it = ms.begin();
    while (it != ms.end()) {
        if (*it >= low && *it <= high) it = ms.erase(it);
        else ++it;
    }
}

void task1_addAvgToEnd(std::multiset<double>& ms) {
    if (ms.empty()) return;
    double sum = 0;
    for (double val : ms) sum += val;
    double avg = sum / ms.size();
    ms.insert(avg);
}
void task1_addSumMinMaxToEach(std::multiset<double>& ms) {
    if (ms.size() < 2) return;
    double minVal = *ms.begin();
    double maxVal = *ms.rbegin();
    double sumMinMax = minVal + maxVal;
    
    std::multiset<double> newSet;
    for (double val : ms) newSet.insert(val + sumMinMax);
    ms = newSet;
}

void printMultiset(const std::multiset<double>& ms) {
    for (double val : ms) std::cout << val << " ";
    std::cout << std::endl;
}

void task2_addToMultiset(std::multiset<Pair>& ms, const std::vector<Pair>& values) {
    for (const Pair& p : values) ms.insert(p);
}

void task2_deleteElementsInRange(std::multiset<Pair>& ms, const Pair& low, const Pair& high) {
    auto it = ms.begin();
    while (it != ms.end()) {
        if (low < *it && *it < high) it = ms.erase(it);
        else ++it;
    }
}

void task2_addAvgToEnd(std::multiset<Pair>& ms) {
    if (ms.empty()) return;
    int sumFirst = 0, sumSecond = 0;
    for (const Pair& p : ms) {
        sumFirst += p.first;
        sumSecond += p.second;
    }
    Pair avg(sumFirst / ms.size(), sumSecond / ms.size());
    ms.insert(avg);
}

void task2_addSumMinMaxToEach(std::multiset<Pair>& ms) {
    if (ms.size() < 2) return;
    Pair minPair = *ms.begin();
    Pair maxPair = *ms.rbegin();
    Pair sumMinMax(minPair.first + maxPair.first, minPair.second + maxPair.second);
    
    std::multiset<Pair> newSet;
    for (const Pair& p : ms) {
        newSet.insert(Pair(p.first + sumMinMax.first, p.second + sumMinMax.second));
    }
    ms = newSet;
}

void printPairMultiset(const std::multiset<Pair>& ms) {
    for (const Pair& p : ms) std::cout << p << " ";
    std::cout << std::endl;
}

template<typename T>
class ParameterizedList {
private:
    std::multiset<T> container;

public:
    void addElements(const std::vector<T>& values) {
        for (const T& val : values) container.insert(val);
    }

    void deleteElementsInRange(const T& low, const T& high) {
        auto it = container.begin();
        while (it != container.end()) {
            if (low < *it && *it < high) it = container.erase(it);
            else ++it;
        }
    }

    void addAvgToEnd() {
        if (container.empty()) return;
        
        if constexpr (std::is_same<T, double>::value) {
            double sum = 0;
            for (double val : container) sum += val;
            double avg = sum / container.size();
            container.insert(avg);
        } 
        else if constexpr (std::is_same<T, Pair>::value) {
            int sumFirst = 0, sumSecond = 0;
            for (const Pair& p : container) {
                sumFirst += p.first;
                sumSecond += p.second;
            }
            Pair avg(sumFirst / container.size(), sumSecond / container.size());
            container.insert(avg);
        }
    }

    void addSumMinMaxToEach() {
        if (container.size() < 2) return;
        
        T minVal = *container.begin();
        T maxVal = *container.rbegin();
        
        if constexpr (std::is_same<T, double>::value) {
            double sumMinMax = minVal + maxVal;
            std::multiset<T> newSet;
            for (T val : container) newSet.insert(val + sumMinMax);
            container = newSet;
        }
        else if constexpr (std::is_same<T, Pair>::value) {
            Pair sumMinMax(minVal.first + maxVal.first, minVal.second + maxVal.second);
            std::multiset<T> newSet;
            for (const Pair& p : container) {
                newSet.insert(Pair(p.first + sumMinMax.first, p.second + sumMinMax.second));
            }
            container = newSet;
        }
    }

    void print() const {
        for (const T& val : container) std::cout << val << " ";
        std::cout << std::endl;
    }

    size_t size() const { return container.size(); }
};

int main() {
    std::cout << "========== TASK 1: multiset<double> ==========" << std::endl;
    std::multiset<double> ms1;
    std::vector<double> init1 = {1.5, 2.3, 4.7, 5.1, 2.3, 3.9, 6.2, 1.5};
    task1_addToMultiset(ms1, init1);
    std::cout << "Initial multiset: "; printMultiset(ms1);
    
    task1_addAvgToEnd(ms1);
    std::cout << "After adding average to end: "; printMultiset(ms1);
    
    task1_deleteElementsInRange(ms1, 2.0, 5.0);
    std::cout << "After deleting elements in [2.0,5.0]: "; printMultiset(ms1);
    
    task1_addSumMinMaxToEach(ms1);
    std::cout << "After adding sum(min+max) to each: "; printMultiset(ms1);
    
    std::cout << "\n========== TASK 2: multiset<Pair> ==========" << std::endl;
    std::multiset<Pair> ms2;
    std::vector<Pair> init2 = {Pair(1,2), Pair(3,4), Pair(5,6), Pair(1,2), Pair(7,8), Pair(3,4)};
    task2_addToMultiset(ms2, init2);
    std::cout << "Initial multiset: "; printPairMultiset(ms2);
    
    task2_addAvgToEnd(ms2);
    std::cout << "After adding average to end: "; printPairMultiset(ms2);
    
    task2_deleteElementsInRange(ms2, Pair(2,3), Pair(6,7));
    std::cout << "After deleting elements in range (2,3) to (6,7): "; printPairMultiset(ms2);
    
    task2_addSumMinMaxToEach(ms2);
    std::cout << "After adding sum(min+max) to each: "; printPairMultiset(ms2);
    
    std::cout << "\n========== TASK 3: ParameterizedList<double> ==========" << std::endl;
    ParameterizedList<double> list1;
    std::vector<double> init3 = {1.5, 2.3, 4.7, 5.1, 2.3, 3.9};
    list1.addElements(init3);
    std::cout << "Initial list: "; list1.print();
    
    list1.addAvgToEnd();
    std::cout << "After adding average: "; list1.print();
    
    list1.deleteElementsInRange(2.0, 5.0);
    std::cout << "After deleting in (2.0,5.0): "; list1.print();
    
    list1.addSumMinMaxToEach();
    std::cout << "After adding sum(min+max): "; list1.print();
    
    std::cout << "\n========== TASK 3: ParameterizedList<Pair> ==========" << std::endl;
    ParameterizedList<Pair> list2;
    std::vector<Pair> init4 = {Pair(1,2), Pair(3,4), Pair(5,6), Pair(1,2), Pair(7,8)};
    list2.addElements(init4);
    std::cout << "Initial list: "; list2.print();
    
    list2.addAvgToEnd();
    std::cout << "After adding average: "; list2.print();
    
    list2.deleteElementsInRange(Pair(2,3), Pair(6,7));
    std::cout << "After deleting in range: "; list2.print();
    
    list2.addSumMinMaxToEach();
    std::cout << "After adding sum(min+max): "; list2.print();
    
    return 0;
}
