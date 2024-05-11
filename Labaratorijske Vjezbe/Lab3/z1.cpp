// Autor: Muhamed Husić
#include <iostream>
#include <cmath>
#include <vector>
//predznak od broja pa modul
int SumaCifara(int broj) {
    int suma{0};
    while(broj != 0) {
        int cifra = broj % 10;
        broj /= 10;
        suma += cifra;
    }
    return suma;
}

std::vector<int> IzdvojiElemente(std::vector<int> vektor, bool parnost) {
    std::vector<int> rezultat;
    for(int x : vektor) {
        if(parnost && SumaCifara(x) % 2 == 0) {
            rezultat.push_back(x);
        } else if(!parnost && SumaCifara(x) % 2 != 0) {
            rezultat.push_back(x);
        }
    }
    return rezultat;
}

int main ()
{
    std::cout << "Koliko zelite unijeti elemenata: ";
    int br_elemenata;
    std::cin >> br_elemenata;
    if(br_elemenata <= 0) {
        std::cout << "Broj elemenata mora biti veci od 0!";
        return 0;
    }
    std::cout << "Unesite elemente: ";
    std::vector<int> vektor;
    for(int i=0; i<br_elemenata; i++) {
        int element;
        std::cin >> element;
        vektor.push_back(element);
    }
    std::vector<int> paran, neparan;
    paran = IzdvojiElemente(vektor, true);
    neparan = IzdvojiElemente(vektor, false);
	if(!paran.empty()) {
        for(int x : paran) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
    }
    if(!neparan.empty()) {
        for(int x : neparan) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
