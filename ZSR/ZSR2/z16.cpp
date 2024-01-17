#include <iostream>
#include <vector>
#include <cmath>

std::vector<int> Korijen(int broj) {
    std::vector<int> rezultat;
    for(int i=1; i<broj; i++) {
        if(std::sqrt(i) == static_cast<int>(std::sqrt(i))) {
            rezultat.push_back(i);
        }
    }
    return rezultat;
}

int main() {
    std::cout << "Unesite broj: ";
    int n;
    std::cin >> n;
    std::cout << "Dati vektor glasi: ";
    std::vector<int> vektor = Korijen(n);
    for(int x : vektor) std::cout << x << "\t";
    std::cout << std::endl;
    return 0;
}