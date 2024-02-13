#include <iostream>
#include <cmath>
#include <complex>

int main() {
    std::cout 
    << "Unesite kompleksni broj z(unos obaviti unutar zagrada '()'), te nakon toga dva realna broja: ";
    std::complex<double>z;
    double x, y;
    while(!(std::cin >> z >> x >> y)) {
        std::cout << "Pogresan unos, unesite sve ispocetka!" << std::endl;
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cin.clear();
        std::cin.ignore(1000, '\n');
    }
    z=std::pow((x + std::complex<double>(0, 5.) / (std::pow(z, 3) * sqrt(x - std::complex<double>(0, y)))), 2);
    std::cout << "Rezultat je: "  << z.real() << " + " << z.imag() << "i." << std::endl;
    return 0;
}