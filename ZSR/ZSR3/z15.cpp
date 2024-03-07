#include <iostream>
#include <cmath>

int BezNula(int broj) {
    int brojac = 0;
    int rezultat;
    while(broj != 0) {
        int privremeni_br = broj % 10;
        broj /= 10;
        if(privremeni_br != 0) {
            rezultat += (privremeni_br * std::pow(10, brojac));
            brojac++;
        }
    }
    return rezultat;
}

int main() {
    std::cout << "Unesite brojeve, 0 za kraj: ";
    int x;
    do {
        std::cin >> x;
        std::cout << BezNula(x) << std::endl;
    }while(x != 0);
    
    return 0;
}