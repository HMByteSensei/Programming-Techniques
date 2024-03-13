#include <iostream>

double UnesiBroj() {
    double broj;
    while(!(std::cin >> broj)) {
        std::cout << "Neispravan unos. Molimo, pokušajte ponovo." << std::endl;
        std::cin.ignore(1000, '\n');
        std::cin.clear();
    }
    return broj;
}

int main() {
    double a{UnesiBroj()}, b{UnesiBroj()}, c{UnesiBroj()}; //jednoobrazna inicijalizacija
    //ax + b = c
    if(a == 0) {
        std::cout << "Rjesenje ne postoji." << std::endl; 
    } else {
        std::cout << "Rjesenje date linearne jednacine je: " << (c-b) / a << std::endl;
    }
    return 0;
}