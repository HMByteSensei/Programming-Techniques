#include <iostream>
#include <array>
#include <cmath>
#include <vector>

std::vector<int> PretvoriUVektor(std::array<int, 10> lista, int broj_elemenata) {
    std::vector<int> vektor;//(broj_elemenata);
    for(int i=(broj_elemenata-1); i>=0; i--) {
        vektor.push_back(lista.at(i));
    }
    return vektor;
}

int main() {
    std::cout << "Unesi broj elemenata koji moze biti manji ili jednak broju 10: ";
    int n;
    std::cin >> n;
    if(std::cin.fail()) {
        std::exit(0);
    }
    if(n > 10 || n <= 0) {
        std::exit(0);
    }
    std::cout << "Unesite elemente: ";
    std::array<int, 10> lista{0};
    for(int i=0; i<n; i++) {
        int element;
        std::cin >> element;
        lista.at(i) = element;
    }
    std::vector<int> vektor = PretvoriUVektor(lista, n);
    std::cout << "Elementi modernog niza su redom: \n";
    for(int x : lista) std::cout << x << "\t";
    std::cout << std::endl;
    std::cout << "Elementi vektora su redom: \n";
    for(int x : vektor) std::cout << x << "\t";
    std::cout << std::endl;
}