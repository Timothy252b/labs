#include "Person.h"

class Vector {
    Person** pArr;
    int size;
    int cur;
public:
    Vector() : pArr(0), size(0), cur(0) {}
    Vector(int a) {
        pArr = new Person*[a];
        size = a;
        cur = 0;
    }
    ~Vector() {
        delete[] pArr;
    }
    void Add(Person* p) {
        if (cur < size) {
            pArr[cur] = p;
            cur++;
        }else
            std::cout << "something wrong!" << std::endl;
    }
    friend std::ostream& operator<<(std::ostream& cout, const Vector& v);
};
