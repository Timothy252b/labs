#include "Student.h"
#include "Vector.h"

int main() {
    Student s;
    Student t("Jan", 67, "Godword", 3);
    std::cout << s;
    std::cout << t;
    Person* p = &t;
    p->Show();
    s.Show();
    t.Show();
    t.isGood();
    Vector v(5);
    for (int i = 0; i < 5; i++) {
        v.Add(&s);
    }
    std::cout << v;
    return 0;
}
