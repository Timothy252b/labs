#include <iostream>
#include <string>
using namespace std;

bool isPrime(int n){
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 3; i * i <= n; i += 2){
        if (n % i == 0) return false;
    }
    return true;
}

int getNthPrime(int n){
    if (n < 0) return 2;
    int count = 0;
    int num = 2;
    while (true) {
        if (isPrime(num)) {
            if (count == n) return num;
            count++;
        }
        num++;
    }
}

struct HashTable {
    string* table;
    int size;
    int count;
    
    HashTable(int n) {
        int primeSize = n;
        while (!isPrime(primeSize)) primeSize++;
        table = new string[primeSize]();
        size = primeSize;
        count = 0;
    }
    
    ~HashTable() {
        delete[] table;
    }
    
    int hash(const string& s) {
        long long sum = 0;
        for (int i = 0; i < s.length(); i++) {
            sum += (long long)getNthPrime(i) * s[i];
        }
        return sum % size;
    }
    
    void resize() {
        int newSize = size * 2;
        while (!isPrime(newSize)) newSize++;
        
        string* newTable = new string[newSize]();
        
        for (int i = 0; i < size; i++) {
            if (table[i] != "") {
                long long sum = 0;
                for (int j = 0; j < table[i].length(); j++) {
                    sum += (long long)getNthPrime(j) * table[i][j];
                }
                int newIndex = sum % newSize;
                while (newTable[newIndex] != "") {
                    newIndex = (newIndex + 1) % newSize;
                }
                newTable[newIndex] = table[i];
            }
        }
        
        delete[] table;
        table = newTable;
        size = newSize;
    }
    
    void insert(const string& s) {
        if (search(s)) return;
        
        if ((double)count / size >= 0.7) {
            resize();
        }
        
        int index = hash(s);
        int startIndex = index;
        
        while (table[index] != "") {
            index = (index + 1) % size;
            if (index == startIndex) {
                resize();
                insert(s);
                return;
            }
        }
        
        table[index] = s;
        count++;
    }
    
    bool search(const string& s) {
        int index = hash(s);
        int startIndex = index;
        
        while (table[index] != "") {
            if (table[index] == s) {
                return true;
            }
            index = (index + 1) % size;
            if (index == startIndex) break;
        }
        return false;
    }
    
    void remove(const string& s) {
        int index = hash(s);
        int startIndex = index;
        
        while (table[index] != "") {
            if (table[index] == s) {
                table[index] = "";
                count--;
                
                // Rehash subsequent elements
                int nextIndex = (index + 1) % size;
                while (table[nextIndex] != "") {
                    string temp = table[nextIndex];
                    table[nextIndex] = "";
                    count--;
                    insert(temp);
                    nextIndex = (nextIndex + 1) % size;
                }
                return;
            }
            index = (index + 1) % size;
            if (index == startIndex) break;
        }
    }
    
    void print() {
        for (int i = 0; i < size; i++) {
            cout << i << ": ";
            if (table[i] == "") {
                cout << "(empty)" << endl;
            } else {
                cout << table[i] << endl;
            }
        }
    }
    
    void stats() {
        int filled = 0;
        int maxProbe = 0;
        
        for (int i = 0; i < size; i++) {
            if (table[i] != "") {
                filled++;
                // Calculate probe length for this element (optional)
            }
        }
        
        cout << "\n=== Hash Table Statistics ===" << endl;
        cout << "Size:           " << size << endl;
        cout << "Elements:       " << count << endl;
        cout << "Load factor:    " << (double)count / size << endl;
        cout << "Filled buckets: " << filled << endl;
        cout << "Empty buckets:  " << size - filled << endl;
    }
    
    void displayWithHash() {
        cout << "\n=== Hash Table with Hash Values ===" << endl;
        for (int i = 0; i < size; i++) {
            cout << i << ": ";
            if (table[i] == "") {
                cout << "(empty)" << endl;
            } else {
                long long sum = 0;
                for (int j = 0; j < table[i].length(); j++) {
                    sum += (long long)getNthPrime(j) * table[i][j];
                }
                int h = sum % size;
                cout << table[i] << " (hash=" << h << ")" << endl;
            }
        }
    }
    
    void clear() {
        delete[] table;
        table = new string[size]();
        count = 0;
    }
    
    int getSize() { return size; }
    int getCount() { return count; }
};

int main() {
    cout << "=== Hash Table Demo ===" << endl;
    HashTable h(10);
    
    cout << "\n--- Insertion ---" << endl;
    h.insert("good");
    h.insert("bad");
    h.insert("sad");
    h.insert("sadistic");
    h.insert("sister");
    h.print();
    
    cout << "\n--- Search ---" << endl;
    cout << "Search 'good': " << (h.search("good") ? "Found" : "Not found") << endl;
    cout << "Search 'happy': " << (h.search("happy") ? "Found" : "Not found") << endl;
    
    cout << "\n--- Insert more (trigger resize) ---" << endl;
    h.insert("apple");
    h.insert("banana");
    h.insert("cherry");
    h.insert("dog");
    h.insert("cat");
    h.insert("elephant");
    h.insert("flower");
    h.print();
    
    cout << "\n--- Remove ---" << endl;
    cout << "Removing 'bad'" << endl;
    h.remove("bad");
    cout << "Removing 'sister'" << endl;
    h.remove("sister");
    h.print();
    
    h.stats();
    h.displayWithHash();
    
    return 0;
}