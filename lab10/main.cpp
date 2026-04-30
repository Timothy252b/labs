#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

class Pair {
private:
    int first;
    double second;

public:
    Pair() : first(0), second(0.0) {}
    Pair(int f, double s) : first(f), second(s) {}

    int getFirst() const { return first; }
    double getSecond() const { return second; }
    void setFirst(int f) { first = f; }
    void setSecond(double s) { second = s; }

    Pair operator-(const Pair& other) const {
        return Pair(first - other.first, second - other.second);
    }

    Pair operator+(int constVal) const {
        return Pair(first + constVal, second);
    }

    Pair operator+(double constVal) const {
        return Pair(first, second + constVal);
    }

    bool operator<(const Pair& other) const {
        if (first != other.first) return first < other.first;
        return second < other.second;
    }

    bool operator==(const Pair& other) const {
        return first == other.first && second == other.second;
    }

    friend std::ostream& operator<<(std::ostream& os, const Pair& p) {
        os << p.first << ":" << p.second;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Pair& p) {
        std::cout << "Enter first (int): ";
        is >> p.first;
        std::cout << "Enter second (double): ";
        is >> p.second;
        return is;
    }
};

void saveToFile(const std::string& filename, const std::vector<Pair>& data) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) return;
    size_t size = data.size();
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));
    file.write(reinterpret_cast<const char*>(data.data()), size * sizeof(Pair));
}

std::vector<Pair> loadFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) return {};
    size_t size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));
    std::vector<Pair> data(size);
    file.read(reinterpret_cast<char*>(data.data()), size * sizeof(Pair));
    return data;
}

void displayAll(const std::vector<Pair>& data) {
    if (data.empty()) {
        std::cout << "No records found.\n";
        return;
    }
    for (size_t i = 0; i < data.size(); ++i) {
        std::cout << i + 1 << ". " << data[i] << "\n";
    }
}

void createAndSave(const std::string& filename) {
    int n;
    std::cout << "How many pairs to create? ";
    std::cin >> n;
    std::vector<Pair> data;
    for (int i = 0; i < n; ++i) {
        std::cout << "\nPair " << i + 1 << ":\n";
        Pair p;
        std::cin >> p;
        data.push_back(p);
    }
    saveToFile(filename, data);
    std::cout << "Saved to file.\n";
}

void readAndDisplay(const std::string& filename) {
    std::vector<Pair> data = loadFromFile(filename);
    displayAll(data);
}

void deleteLessThan(const std::string& filename) {
    Pair threshold;
    std::cout << "Enter threshold pair:\n";
    std::cin >> threshold;
    
    std::vector<Pair> data = loadFromFile(filename);
    size_t original = data.size();
    data.erase(std::remove_if(data.begin(), data.end(),
        [&threshold](const Pair& p) { return p < threshold; }), data.end());
    
    saveToFile(filename, data);
    std::cout << "Deleted " << original - data.size() << " records.\n";
}

void increaseByL(const std::string& filename) {
    Pair target;
    std::cout << "Enter target pair value:\n";
    std::cin >> target;
    
    double L;
    std::cout << "Enter L (number to add): ";
    std::cin >> L;
    
    std::vector<Pair> data = loadFromFile(filename);
    int count = 0;
    
    for (auto& p : data) {
        if (p == target) {
            if (L == static_cast<int>(L)) {
                p = p + static_cast<int>(L);
            } else {
                p = p + L;
            }
            count++;
        }
    }
    
    saveToFile(filename, data);
    std::cout << "Increased " << count << " records.\n";
}

void addAfterPosition(const std::string& filename) {
    int position, K;
    std::cout << "Enter position (1-based): ";
    std::cin >> position;
    std::cout << "Enter K (number of records to add): ";
    std::cin >> K;
    
    if (position < 1) {
        std::cout << "Invalid position.\n";
        return;
    }
    
    std::vector<Pair> data = loadFromFile(filename);
    
    if (position > static_cast<int>(data.size())) {
        std::cout << "Position out of range.\n";
        return;
    }
    
    std::vector<Pair> newRecords;
    for (int i = 0; i < K; ++i) {
        std::cout << "\nNew record " << i + 1 << ":\n";
        Pair p;
        std::cin >> p;
        newRecords.push_back(p);
    }
    
    data.insert(data.begin() + position, newRecords.begin(), newRecords.end());
    saveToFile(filename, data);
    std::cout << "Added " << K << " records after position " << position << ".\n";
}

int main() {
    std::string filename = "pairs.dat";
    int choice;
    
    do {
        std::cout << "\n========== MENU ==========\n";
        std::cout << "1. Create and save records\n";
        std::cout << "2. Read and display all records\n";
        std::cout << "3. Delete all records less than given value\n";
        std::cout << "4. Increase records with given value by L\n";
        std::cout << "5. Add K records after specified position\n";
        std::cout << "6. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        
        switch (choice) {
            case 1: createAndSave(filename); break;
            case 2: readAndDisplay(filename); break;
            case 3: deleteLessThan(filename); break;
            case 4: increaseByL(filename); break;
            case 5: addAfterPosition(filename); break;
            case 6: std::cout << "Goodbye!\n"; break;
            default: std::cout << "Invalid choice.\n";
        }
    } while (choice != 6);
    
    return 0;
}
