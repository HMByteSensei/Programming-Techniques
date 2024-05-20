#include <iostream>
#include <cmath>
#include <deque>

int SumaCifara(int broj) {
    int suma{0};
    while(broj != 0) {
        int cifra = broj % 10;
        broj /= 10;
        suma += cifra;
    }
    return suma;
}
// Autor: Muhamed Husić
std::deque<int> IzdvojiElemente(std::deque<int> vektor, bool parnost) {
    std::deque<int> rezultat;
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
    std::deque<int> vektor;
    for(int i=0; i<br_elemenata; i++) {
        int element;
        std::cin >> element;
        vektor.push_back(element);
    }
    std::deque<int> paran, neparan;
    paran = IzdvojiElemente(vektor, true);
    neparan = IzdvojiElemente(vektor, false);
	if(!paran.empty()) {
        for(int i=0; i<paran.size()-1; i++) {
            std::cout << paran.at(i) << ",";
        }
        std::cout << paran.at(paran.size() - 1) << std::endl;
    }
    if(!neparan.empty()) {
        for(int i=0; i<neparan.size()-1; i++) {
            std::cout << neparan.at(i) << ",";
        }
        std::cout << neparan.at(neparan.size() - 1) << std::endl;
    }
    return 0;
}
