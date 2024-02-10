#include<iostream>
#include <vector>
#include <cmath>

std::vector<int> ParNepar(std::vector<int> vektor) {
    std::vector<int> rezultat;
    for(int i=0; i<vektor.size(); i++) {
        int brojac=0, suma=0;
        bool poz{true};
        if(vektor.at(i) < 0) poz = false;
        while(vektor.at(i) != 0) {
            int vrijednost = static_cast<int>(std::fabs(vektor.at(i))) % 10;
            vektor.at(i) /= 10;
            if((vrijednost % 2) == 0) {
                vrijednost += 1;
            }
            else {
                vrijednost -= 1;
            }
            suma += vrijednost * std::pow(10, brojac);
            brojac++;
        }
        if(poz) rezultat.push_back(suma);
        else rezultat.push_back(-suma);

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
    std::vector<int> rezultat = ParNepar(vektor);
    for(int x : rezultat) std::cout << x << "\t";
    std::cout << std::endl;
    return 0;
}
/*354126079, odgovarajući element u vektoru koji 
predstavlja rezultat treba da glasi 245037168. Slično, od broja  354126079 treba nastati broj  245037168.*/