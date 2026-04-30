#include "Vector.h"

std::ostream& operator<<(std::ostream& cout, const Vector& v) {
    for (int i = 0; i < v.cur; i++){
        v.pArr[i]->Show();
    }
    return cout;
}
