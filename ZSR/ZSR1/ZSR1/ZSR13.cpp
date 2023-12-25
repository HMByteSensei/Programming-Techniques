#include <iostream>
#include <cmath>

int main() {
    std::cout << "Unesite brojeve, 0 za kraj: ";
    double broj, suma{0}, proizvod{1}; //jednoobrazna inicijalizacija
    int brojac(0); //konstruktorska inicijalizacija
    do {
        std::cin >> broj;
        suma += broj;
        if(broj != 0) 
        {
            proizvod *= broj;
            brojac++;
        }
    }while(broj != 0);
    std::cout << "Aritmeticka sredina je: " << (suma / brojac) << ", a geometrijska sredina je: "
    << std::pow(proizvod, 1.0/brojac) << std::endl;
    return 0;
}