#include <iostream>
#include <list>
#include <queue>
#include <map>
#include <algorithm>
#include <numeric>
#include <vector>

struct Pair {
    int first;
    int second;

    Pair(int f = 0, int s = 0) : first(f), second(s) {}

    bool operator==(const Pair& other) const {
        return first == other.first && second == other.second;
    }

    bool operator<(const Pair& other) const {
        return first < other.first;
    }
};

std::ostream& operator<<(std::ostream& os, const Pair& p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

void task1() {
    std::cout << "\n=== TASK 1: LIST ===\n";
    std::list<Pair> lst = {{5,1}, {2,9}, {5,3}, {7,4}, {2,5}, {5,6}, {8,7}};
    std::cout << "Initial: "; for(auto& p : lst) std::cout << p << " "; std::cout << "\n";

    std::replace_if(lst.begin(), lst.end(), [](const Pair& p){ return p.first == 5; }, Pair(0,0));
    std::cout << "After replace_if (first==5 -> (0,0)): "; for(auto& p : lst) std::cout << p << " "; std::cout << "\n";

    lst.remove_if([](const Pair& p){ return p.first == 0; });
    std::cout << "After remove_if (first==0): "; for(auto& p : lst) std::cout << p << " "; std::cout << "\n";

    lst.sort([](const Pair& a, const Pair& b){ return a.first < b.first; });
    std::cout << "Sorted ascending by first: "; for(auto& p : lst) std::cout << p << " "; std::cout << "\n";

    lst.sort([](const Pair& a, const Pair& b){ return a.first > b.first; });
    std::cout << "Sorted descending by first: "; for(auto& p : lst) std::cout << p << " "; std::cout << "\n";

    auto it = std::find_if(lst.begin(), lst.end(), [](const Pair& p){ return p.first == 7; });
    if(it != lst.end()) std::cout << "Found element with first==7: " << *it << "\n";

    int cnt = std::count_if(lst.begin(), lst.end(), [](const Pair& p){ return p.first == 2; });
    std::cout << "Count of elements with first==2: " << cnt << "\n";

    if(!lst.empty()) {
        auto [minIt, maxIt] = std::minmax_element(lst.begin(), lst.end(), 
            [](const Pair& a, const Pair& b){ return a.first < b.first; });
        int sumMinMax = minIt->first + maxIt->first;
        std::for_each(lst.begin(), lst.end(), [sumMinMax](Pair& p){ p.first += sumMinMax; });
        std::cout << "After adding (min+max=" << sumMinMax << ") to each first: "; 
        for(auto& p : lst) std::cout << p << " "; std::cout << "\n";
    }
}

void task2() {
    std::cout << "\n=== TASK 2: PRIORITY QUEUE ===\n";
    std::priority_queue<Pair> pq;
    std::vector<Pair> data = {{3,1}, {1,2}, {4,3}, {1,4}, {2,5}};
    
    for(auto& p : data) pq.push(p);
    std::cout << "Priority queue (max-heap by first): ";
    auto temp = pq;
    while(!temp.empty()) { std::cout << temp.top() << " "; temp.pop(); }
    std::cout << "\n";

    std::vector<Pair> vec;
    while(!pq.empty()) { vec.push_back(pq.top()); pq.pop(); }
    
    std::replace_if(vec.begin(), vec.end(), [](const Pair& p){ return p.first == 1; }, Pair(9,9));
    std::cout << "After replace_if (first==1 -> (9,9)): "; for(auto& p : vec) std::cout << p << " "; std::cout << "\n";

    auto newEnd = std::remove_if(vec.begin(), vec.end(), [](const Pair& p){ return p.first == 9; });
    vec.erase(newEnd, vec.end());
    std::cout << "After remove_if (first==9): "; for(auto& p : vec) std::cout << p << " "; std::cout << "\n";

    std::sort(vec.begin(), vec.end(), [](const Pair& a, const Pair& b){ return a.first < b.first; });
    std::cout << "Sorted ascending: "; for(auto& p : vec) std::cout << p << " "; std::cout << "\n";

    std::sort(vec.begin(), vec.end(), [](const Pair& a, const Pair& b){ return a.first > b.first; });
    std::cout << "Sorted descending: "; for(auto& p : vec) std::cout << p << " "; std::cout << "\n";

    auto it = std::find_if(vec.begin(), vec.end(), [](const Pair& p){ return p.first == 2; });
    if(it != vec.end()) std::cout << "Found element with first==2: " << *it << "\n";

    int cnt = std::count_if(vec.begin(), vec.end(), [](const Pair& p){ return p.first == 4; });
    std::cout << "Count of elements with first==4: " << cnt << "\n";

    if(!vec.empty()) {
        auto [minIt, maxIt] = std::minmax_element(vec.begin(), vec.end(),
            [](const Pair& a, const Pair& b){ return a.first < b.first; });
        int sumMinMax = minIt->first + maxIt->first;
        std::for_each(vec.begin(), vec.end(), [sumMinMax](Pair& p){ p.first += sumMinMax; });
        std::cout << "After adding (min+max=" << sumMinMax << ") to each first: ";
        for(auto& p : vec) std::cout << p << " "; std::cout << "\n";
    }
}

void task3() {
    std::cout << "\n=== TASK 3: MAP (DICTIONARY) ===\n";
    std::map<int, int> m = {{5,1}, {2,9}, {7,4}, {8,7}, {3,6}};
    std::cout << "Initial map: ";
    for(auto& [k,v] : m) std::cout << "(" << k << "," << v << ") "; 
    std::cout << "\n";

    std::map<int, int> tempMap;
    for(auto& [k,v] : m) {
        if(k == 5) tempMap[0] = 0;
        else tempMap[k] = v;
    }
    m = tempMap;
    std::cout << "After replacing key 5 with (0,0): ";
    for(auto& [k,v] : m) std::cout << "(" << k << "," << v << ") "; 
    std::cout << "\n";

    auto it = m.begin();
    while(it != m.end()) {
        if(it->first >= 2 && it->first <= 5) it = m.erase(it);
        else ++it;
    }
    std::cout << "After removing keys in [2,5]: ";
    for(auto& [k,v] : m) std::cout << "(" << k << "," << v << ") "; 
    std::cout << "\n";

    std::cout << "Map is always sorted ascending by key: ";
    for(auto& [k,v] : m) std::cout << "(" << k << "," << v << ") "; 
    std::cout << "\n";

    auto found = m.find(8);
    if(found != m.end()) std::cout << "Found element with key 8: (" << found->first << "," << found->second << ")\n";

    int cnt = std::count_if(m.begin(), m.end(), [](const auto& p){ return p.first > 0; });
    std::cout << "Count of elements with key>0: " << cnt << "\n";

    if(!m.empty()) {
        int sum = std::accumulate(m.begin(), m.end(), 0, [](int s, const auto& p){ return s + p.second; });
        double mean = static_cast<double>(sum) / m.size();
        std::cout << "Arithmetic mean of values: " << mean << "\n";
        
        m[static_cast<int>(mean)] = 0;
        std::cout << "After adding mean as new key: ";
        for(auto& [k,v] : m) std::cout << "(" << k << "," << v << ") "; 
        std::cout << "\n";
    }

    if(!m.empty()) {
        int minKey = m.begin()->first;
        int maxKey = m.rbegin()->first;
        int sumMinMaxKey = minKey + maxKey;
        
        std::map<int,int> modified;
        for(auto& [k,v] : m) {
            modified[k + sumMinMaxKey] = v;
        }
        m = modified;
        std::cout << "After adding (minKey+maxKey=" << sumMinMaxKey << ") to each key: ";
        for(auto& [k,v] : m) std::cout << "(" << k << "," << v << ") "; 
        std::cout << "\n";
    }
}

int main() {
    task1();
    task2();
    task3();
    return 0;
}
