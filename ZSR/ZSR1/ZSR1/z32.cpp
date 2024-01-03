#include <iostream>
#include <iomanip>

int SumaDjelioca(int broj) {
    int suma = 0;
    for(int i=1; i<=broj; i++) {
        if(broj % i == 0) {
            suma += i;
        }
    }
    return suma;
}

int main() {
    std::cout << "Unesite prirodne brojeve n i m: ";
    double n, m;
    while(!(std::cin >> n >> m) || m<n || m!=int(m) || n!=int(n)) {
        std::cout << "Pogresan unos!" << std::endl;
        if(std::cin.fail()) {
            std::cin.ignore(1000, '\n');
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cin.clear();
        }
    }
    std::cout << std::setw(25) << std::setfill('-') << "" << std::endl;
    std::cout.fill(' ');
    for(; n<=m; n++) {
        std::cout << "| " << std::left << std::setw(10) << n << "|" << std::right << std::setw(10) 
        << SumaDjelioca(n) << " |" << std::endl;
    }
    std::cout << std::setw(25) << std::setfill('-') << "" << std::endl;
    std::cout.fill(' ');
    return 0;
}