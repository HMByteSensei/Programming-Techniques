#include <iostream>
#include <cmath>
#include <vector>

std::vector<int> NajmanjeCifre(std::vector<int> vektor) {
    std::vector<int> rezultat;
    for(int i=0; i<vektor.size(); i++) {
        int min_br{10};
        bool poz = true;
        if(vektor.at(i) < 0) poz = false;
        while(vektor.at(i) != 0) {
            int privremeni = static_cast<int>(std::fabs(vektor.at(i))) % 10;
            vektor.at(i) /= 10;
            if(privremeni < min_br) {
                min_br = privremeni;
            }
        }
        if(poz) rezultat.push_back(min_br);
        else rezultat.push_back(-min_br);
    }
    return rezultat;
}

int main() {
    std::cout << "Unesite prirodan broj n: ";
    int n;
    std::cin >> n;
    if(std::cin.fail()) {
        std::cin.clear(); 
        std::cin.ignore(1000, '\n');
        std::exit(0);
    }
    std::vector<int> vektor(n);
    for(int i=0; i<n; i++) {
        double element;
        while(!(std::cin >> element) || static_cast<int>(element) != element) {
            std::cout << "Pogresan unos!" << "\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
        vektor.at(i) = element;
    }
    for(int i=0; i<n; i++) std::cout << "Trazeni element je: " << NajmanjeCifre(vektor).at(i) << std::endl;;
    return 0;
}