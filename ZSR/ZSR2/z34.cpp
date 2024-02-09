#include<iostream>
#include <vector>
#include <cmath>

int Faktor(int broj) {
    if(broj != 0) {
        return broj * Faktor(broj-1);
    }
    else return 1;
}

std::vector<int> Faktorijel(std::vector<int> vektor) {
    std::vector<int> rezultat;
    for(int i=0; i<vektor.size(); i++) {
        if(vektor.at(i) < 0) rezultat.push_back(0);
        else {
            rezultat.push_back(Faktor(vektor.at(i)));
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
    std::vector<int> rezultat = Faktorijel(vektor);
    for(int x : rezultat) std::cout << x << "\t";
    std::cout << std::endl;
    return 0;
}