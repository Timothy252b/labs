#include "Aj.h"

void Aj::Init(double f, int s){
    first = f;
    second = s;
}
void Aj::Read(){
    std::cout << "Enter a0: ";
    std::cin >> first;
    std::cout << "Enter r: ";
    std::cin >> second;
}
void Aj::Show(){
    std::cout << "a0: " << first << " r: " << second << std::endl;
}
double Aj::element(int j){
    if (j < 0) return -1;
    return first*pow(second, j);
}
