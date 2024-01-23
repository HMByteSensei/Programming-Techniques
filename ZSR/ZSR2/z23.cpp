#include<iostream>
#include <vector>
#include <cmath>

std::vector<int> SlozeniBrojevi(std::vector<int> vektor) {
    std::vector<int> rezultat;
    for(int i=0; i<vektor.size(); i++) {
        bool prost = true;
        for(int j=2; j<(vektor.at(i)/2 + 1); j++) {
            if((vektor.at(i) % j) == 0) {
                prost = false;
            }
        }
        if(!prost) rezultat.push_back(vektor.at(i));
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
    std::vector<int> rezultat = SlozeniBrojevi(vektor);
    for(int x : rezultat) std::cout << x << "\t";
    std::cout << std::endl;
    return 0;
}