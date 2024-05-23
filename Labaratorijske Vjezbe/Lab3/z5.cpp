#include <iostream>
#include <cmath>
#include <deque>
// Autor: Muhamed Husic
int SumaCifara(int broj) {
    int suma{0};
    while(broj != 0) {
        int cifra = broj % 10;
        broj /= 10;
        suma += cifra;
    }
    return suma;
}

std::deque<int> IzdvojiElemente(std::deque<int> vektor, bool parnost) {
    std::deque<int> rezultat;
    for(int i=vektor.size()-1; i>=0; i--) {
        if(parnost && SumaCifara(vektor.at(i)) % 2 == 0) {
            rezultat.push_front(vektor.at(i));
        } else if(!parnost && SumaCifara(vektor.at(i)) % 2 != 0) {
            rezultat.push_front(vektor.at(i));
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
