#include <iostream>
#include <iomanip>

void Ispis(int n) {
    std::cout << "+" << std::setw(n-2) << std::setfill('-') << "" << "+";
    std::cout.fill(' ');
}

int main() {
    std::cout << "Unesite koeficjent n: ";
    int n;
    while(!(std::cin >> n) || (n < 5 || n > 24)) {
        std::cout << "Pogresan unos!" << std::endl;
        std::cin.clear();
        std::cin.ignore(1000, '\n');
    }
    Ispis(2*n);
    std::cout << std::endl;
    for(int i=0; i<(n-2); i++) {
        if(i==0 || i==(n-3)) {
            std::cout << "|" << std::setw(2*(n-1)) << "" << "|" << std::endl;
        } else if(i==1 || i==(n-4)) {
            std::cout << "|" << std::setw(2) << "";
            Ispis(2*(n-3));
            std::cout << std::setw(2) << "" << "|" << std::endl;
        } else {
            std::cout << "|" << std::setw(2) << "" << "|" << std::setw(2*(n-4)) << "" << "|"
            << std::setw(3) << "|" << std::endl; 
        }
    }
    Ispis(2*n);
    std::cout << std::endl;
    return 0;
}