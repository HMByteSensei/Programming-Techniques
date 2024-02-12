#include<iostream>
#include <vector>
#include <cmath>

int BrojDuplikata(std::vector<int> v) {
    std::vector<int> rezultat;
    for(int i=0; i<v.size(); i++) {
        for(int j=i; j<v.size(); j++) {
            if(i == j) continue;
            if(v.at(i) == v.at(j)) {
                rezultat.push_back(v.at(i));
                break;
            }
        }
    }
    int brojac{0};
    for(int i=0; i<rezultat.size(); i++) {
        for(int j=i; j>0; j--) {
            if(rezultat.at(j) == rezultat.at(i)) {
                break;
            }
        }
    }
    return brojac;
}

std::vector<int> OdstraniDuplikate(std::vector<int> v) {
    std::vector<int> rezultat;
    for(int i=0; i<v.size(); i++) {
        bool duplikat = false;
        for(int j=0; j<rezultat.size(); j++) {
            if(v.at(i) == v.at(j)) {
                duplikat = true;
                break;
            }
        }
        if(!duplikat) rezultat.push_back(v.at(i));
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
    std::vector<int> rezultat = OdstraniDuplikate(vektor);
    for(int x : rezultat) std::cout << x << "\t";
    std::cout << std::endl << "Broj duplikata je " << BrojDuplikata(vektor) << std::endl;
    return 0;
}