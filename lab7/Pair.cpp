#include "Pair.h"
template<class t1, class t2>
std::ostream& operator<<(std::ostream& cout, const Pair<t1,t2>& p) {
    return cout << p.getFirst() << ":" << p.getSecond();
}
template <class t1, class t2>
std::istream& operator>>(std::istream& cin, Pair<t1,t2>& p) {
    std::cout << "Enter first: ";
    cin >> p.first;
    std::cout << "Enter second: ";
    cin >> p.stcond;
    return cin;
}
