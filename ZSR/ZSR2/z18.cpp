#include <iostream>
#include <cmath>
#include <vector>
#include <array>

std::vector<int> VektorParniNeparni(std::array<int, 10> moderni_niz, int broj_elemenata) {
    int brojac{0};
    std::vector<int> vektor;
    for(int i=0; i<broj_elemenata; i++) {
        if(moderni_niz.at(i)%2 == 0) {
            vektor.insert(vektor.begin() + brojac, moderni_niz.at(i));
            brojac++;
        } else {
            vektor.push_back(moderni_niz.at(i));
        }
    }
    return vektor;
}

int main() {
    int broj_elemenata = 10;
    std::cout << "Unesite elemente niza!";
    std::array<int, 10> moderni_niz{0};
    for(int i=0; i<broj_elemenata; i++) {
        std::cin >> moderni_niz.at(i);
        if(std::cin.fail()) {
            std::cout << "Ponovite unos!" << std::endl;
            std::cin.clear();
            std::cin.ignore();
            i--;
        }
    }
    std::cout << "Trazeni vektor glasi:\n";
    std::vector<int> vektor = VektorParniNeparni(moderni_niz, broj_elemenata);
    for(int x : vektor) std::cout << x << " ";
    std::cout << std::endl;
    return 0;
}