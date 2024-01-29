#include <iostream>
#include <vector>
#include <cmath>

std::vector<bool> Produkt5UzastopnihBrojeva(std::vector<int> vektor) {
    std::vector<bool> rezultat(vektor.size());
    for(int i=0; i<vektor.size(); i++) {
        if((vektor.at(i) % 120) == 0) {
            rezultat.at(i) = true;
        } else rezultat.at(i) = false;
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
    std::vector<bool> rez = Produkt5UzastopnihBrojeva(vektor);
    for(int x : rez) std::cout << std::boolalpha << x << " ";
    std::cout << std::endl;
    return 0;
}