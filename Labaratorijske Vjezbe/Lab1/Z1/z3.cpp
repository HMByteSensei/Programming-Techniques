// TP 2021/2022: LV 1, Zadatak 3
// Autor Muhamed Husić
#include <cmath>
#include <iomanip>
#include <iostream>

void Red() {
    std::cout << "+" << std::setw(9) << std::setfill('-') << ""
            << "+" << std::setw(10) << ""
            << "+" << std::setw(10) << ""
            << "+" << std::setw(11) << ""
            << "+" << std::endl;
    std::cout.fill(' ');
}

void Zaglavlje() {
    Red();
    std::cout << "| " << std::left << std::setw(8) << "Brojevi"
            << "| " << std::setw(9) << "Kvadrati"
            << "| " << std::setw(9) << "Korijeni"
            << "| " << std::setw(10) << "Logaritmi"
            << "|" << std::endl;
    Red();
}

int main() {
    std::cout << "Unesite pocetnu i krajnju vrijednost: ";
    int a, b;
    std::cin >> a >> b;
    if (a > 9999 || b > 9999) {
    std::exit(0);
    }
    std::cout << std::endl;
    Zaglavlje();
    for (; a <= b; a++) {
    std::cout << "| " << std::left << std::setw(7) << a << " | "  
                << std::right
                << std::setw(8) << a * a << " | " << std::setw(8) << std::fixed
                << std::setprecision(3) << std::sqrt(a) << " | " 
                << std::setw(9)
                << std::setprecision(5) << std::log(a) << " |" <<  std::endl;
    }
    Red();
    return 0;
}