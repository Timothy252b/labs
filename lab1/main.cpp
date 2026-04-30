#include "Aj.h"

int main(){
    Aj a;
    a.Init(1, 2);
    std::cout << a.element(5) << std::endl;
    a.Show();
    a.Read();
    int n;
    std::cout << "Enter j: ";
    std::cin >> n;
    std::cout << a.element(n) << std::endl;
    return 0;
}
