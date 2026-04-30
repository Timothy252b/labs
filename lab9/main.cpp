#include <iostream>
#include <stdexcept>
#include <string>

class ListIndexError : public std::exception {
public:
    const char* what() const noexcept override { return "Index out of range"; }
};

class ListSizeError : public std::exception {
public:
    const char* what() const noexcept override { return "Invalid size"; }
};

class ListMultiplicationError : public std::exception {
public:
    const char* what() const noexcept override { return "Lists have different sizes"; }
};

class List {
private:
    int* data;
    int size;
public:
    List(int s = 0) : size(s) {
        if (s < 0) throw ListSizeError();
        data = (s > 0) ? new int[s]() : nullptr;
    }
    
    List(const List& other) : size(other.size) {
        data = (size > 0) ? new int[size] : nullptr;
        for (int i = 0; i < size; ++i)
            data[i] = other.data[i];
    }
    
    ~List() { delete[] data; }
    
    int& operator[](int index) {
        if (index < 0 || index >= size) throw ListIndexError();
        return data[index];
    }
    
    const int& operator[](int index) const {
        if (index < 0 || index >= size) throw ListIndexError();
        return data[index];
    }
    
    operator int() const {
        return size;
    }
    
    List operator*(const List& other) const {
        if (size != other.size) throw ListMultiplicationError();
        List result(size);
        for (int i = 0; i < size; ++i)
            result.data[i] = data[i] * other.data[i];
        return result;
    }
    
    List& operator+(int n) {
        if (n < 0 || n >= size) throw ListIndexError();
        List* temp = new List(size - n);
        for (int i = n; i < size; ++i)
            temp->data[i - n] = data[i];
        *this = *temp;
        delete temp;
        return *this;
    }
    
    List& operator=(const List& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = (size > 0) ? new int[size] : nullptr;
            for (int i = 0; i < size; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }
    
    void print() const {
        std::cout << "[";
        for (int i = 0; i < size; ++i) {
            std::cout << data[i];
            if (i < size - 1) std::cout << ", ";
        }
        std::cout << "]\n";
    }
    
    void fill(int value) {
        for (int i = 0; i < size; ++i)
            data[i] = value;
    }
};

int main() {
    try {
        List a(5);
        a.fill(2);
        std::cout << "List a: ";
        a.print();
        
        List b(5);
        b.fill(3);
        std::cout << "List b: ";
        b.print();
        
        std::cout << "Size of a: " << (int)a << std::endl;
        
        std::cout << "a[2] = " << a[2] << std::endl;
        
        List c = a * b;
        std::cout << "a * b: ";
        c.print();
        
        List d = a + 2;
        std::cout << "a + 2: ";
        d.print();
        
        std::cout << "\nTesting exceptions:\n";
        
        try {
            std::cout << a[10] << std::endl;
        } catch (const ListIndexError& e) {
            std::cout << "Exception: " << e.what() << std::endl;
        }
        
        try {
            List e(-5);
        } catch (const ListSizeError& e) {
            std::cout << "Exception: " << e.what() << std::endl;
        }
        
        try {
            List x(3);
            List y(4);
            List z = x * y;
        } catch (const ListMultiplicationError& e) {
            std::cout << "Exception: " << e.what() << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cout << "Unexpected: " << e.what() << std::endl;
    }
    
    return 0;
}
