#include <iostream>
#include <cmath>
#include <new>
#include <type_traits>
#include <vector>
#include <typeinfo>
#include <string>
#include <forward_list>

template <typename IterTip>
// zasto ne moze bez *pocetak
auto KreirajIzvrnutiNiz(IterTip pocetak, IterTip iza_kraja) -> typename std::remove_reference_t<decltype(*pocetak)>* {
    // ovo ne podrzava forward_list a nije ni dozvoljeno u zadatku
    // int broj_elemenata = iza_kraja - pocetak;
    int broj_elemenata = 1;
    IterTip temp = pocetak;
    // CUDNO WHILE PETLJA RADI AKO SE STAVI ++temp A NE RADI AKO JE temp++ za 4 AT s forward list
    // izbaci Segmentation fault kao da pristupamo elementu koji nam ne pripada
    while(++temp != iza_kraja) {
        broj_elemenata++;
    }
    typename std::remove_reference_t<decltype(*pocetak)>* niz{};
    try {
        niz = new std::remove_reference_t<decltype(*pocetak)>[broj_elemenata];
    } catch(...) {
        // zasto bad_alloc nece iako je ukljucena biblioteka new
        throw;//std::bad_alloc("Nedovoljno memorije!");
    }
    
    for(int i=0; i<broj_elemenata; i++) {
        niz[broj_elemenata-1-i] = *pocetak++;
    }
    return niz;
}

int main () {
    std::cout << "Koliko zelite elemenata: ";
    int n;
    std::cin >> n;
    std::vector<double> vek;
    try {
        vek.resize(n);
    } catch(std::bad_alloc) {
        std::cout << "Nedovoljno memorije!";
        return 0;
    }
    std::cout << "Unesite elemente: ";
    for(int i=0; i<n; i++) {
        std::cin >> vek.at(i);
    }
    try {
        double *p = KreirajIzvrnutiNiz(vek.begin(), vek.end());
        std::cout << "\nKreirani niz: ";
        for(int i=0; i < n; i++) {
            // std::cout << *p++ << " " ;
            std::cout << p[i] << " ";
        }
        delete[] p;
    } catch(std::bad_alloc& e) {
        std::cout << "Nedovoljno memorije!";
    }
	return 0;
}