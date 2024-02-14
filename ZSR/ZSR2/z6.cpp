#include <iostream>
#include <cmath>
#include <complex>

int main() {
    std::cout << "Unesite realne brojeve x i n: ";
    double x, n;
    while(!(std::cin >> x >> n)) {
        std::cout << "Pogresan unos!\n";
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cin.clear();
        std::cin.ignore(1000, '\n');
    }
    std::complex<double> lijeva = std::pow((cos(x) + sin(x) * std::complex<double>(0, 1)), n);
    std::complex<double> desna = cos(n*x) + sin(n*x) * std::complex<double>(0, 1);
    std::cout << "Lijeva strana je: " << lijeva << ", a desna strana je: " << desna << std::endl;
}