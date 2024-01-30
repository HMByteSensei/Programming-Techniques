#include<iostream>
#include<cmath>

bool DvijeUzastopneCifre(int broj) {
    broj = std::fabs(broj);
    while(broj != 0) {
        int prva = broj % 10;
        broj /= 10;
        int druga = broj % 10;
        if(prva == druga) {
            return true;
        }
    }
    return false;
}

int main() {
    std::cout << "Unesite neki broj: ";
    double broj;
    std::cin >> broj;
    if(!std::cin || broj != static_cast<int>(broj)) {
        std::cout << "Pogresan unos.\n";
        std::cin.ignore(1000, '\n');
        std::cin.clear();
    }
    std::cout << "Broj sadrzi dvije uzastopne, a iste cifre? " << std::boolalpha 
              << DvijeUzastopneCifre(int(broj)) << std::endl;
    return 0;
}