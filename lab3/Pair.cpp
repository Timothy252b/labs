#include "Pair.h"

std::ostream& operator<<(std::ostream& cout, const Pair& p) {
    return cout << p.getFirst() << ":" << p.getSecond();
}
std::istream& operator>>(std::istream& cin, Pair& p) {
    std::string line;
    std::getline(cin, line);
    
    size_t colonPos = line.find(':');
    if (colonPos != std::string::npos) {
        p.first = std::stoi(line.substr(0, colonPos));
        p.second = std::stod(line.substr(colonPos + 1));
    } else {
        cin.setstate(std::ios::failbit);
    }
    return cin;
}
