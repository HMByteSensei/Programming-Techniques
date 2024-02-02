#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

std::vector<int> PrijateljskiBroj(std::vector<int> vektor) {
    std::vector<int> rezultat;
    for(int i=0; i<vektor.size(); i++) {
        int suma{0};
        for(int j=1; j<(vektor.at(i)/2 + 1); j++) { //j=1 jer ne mozemo dijeliti s nulom
            if((vektor.at(i) % j) == 0) {
                suma += j;
            }
        }
        for(int k=0; k<vektor.size(); k++) {
            if(suma == vektor.at(k)) {
                rezultat.push_back(vektor.at(i));
                rezultat.push_back(suma);
            }
        }
    }
    return rezultat;
}
int main() {
    std::cout << "Unesite n: ";
    int n;
    std::cin >> n;
    std::vector<int> vektor(n);
    for(int i=0; i<n; i++) {
        while(!(std::cin >> vektor.at(i))){
            std::cout << "Pogresan unos!\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
    }
    std::vector<int> rez = PrijateljskiBroj(vektor);
    std::cout << std::setw(20) << std::setfill('-') << "" << std::endl;
    std::cout.fill(' ');
    for(int i=0; i<(rez.size()-1);i+=2) {
        std::cout << "|" << std::left << std::setw(8) << rez.at(i) << " | " 
        << std::right << std::setw(8) << rez.at(i+1) << "|" << std::endl;
        std::cout << std::setw(20) << std::setfill('-') << "";
        std::cout << std::endl;
        std::cout.fill(' ');
    }
    return 0;
}