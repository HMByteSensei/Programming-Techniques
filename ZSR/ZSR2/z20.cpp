#include <iostream>
#include <cmath>
#include <vector>

std::vector<int> SumaCifara(std::vector<int>prvi_vektor) {
    std::vector<int> vektor;
    for(int i=0; i<prvi_vektor.size(); i++) {
        int suma{0};
        while(prvi_vektor.at(i) != 0) {
            suma += prvi_vektor.at(i) % 10;
            prvi_vektor.at(i) /= 10;
        }
        vektor.push_back(suma);
    }
    return vektor;
}

int main() {
    std::cout << "Unesite elemente vektora: ";
    int element{0};
    std::vector<int> vektor;
    while(std::cin >> element) {
        if(element == 0) break;
        if(std::cin.fail()) {
            std::cout << "Pogresan unos!";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
        vektor.push_back(element);
    }
    std::cout << "Trazeni vektor glasi: " << std::endl;
    vektor = SumaCifara(vektor);
    for(int x : vektor) std::cout << x << " ";
    std::cout << std::endl;
    return 0;
}