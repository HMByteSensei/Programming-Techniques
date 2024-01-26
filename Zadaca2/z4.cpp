//TP 2022/2023: Zadaća 2, Zadatak 4
#include <cctype>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <typeinfo>

template <typename TipElementaVektora>
bool Kriterij(TipElementaVektora red1, TipElementaVektora red2) {
    std::remove_reference_t<decltype(red1.at(0))> produkt1{}, produkt2{};
    if constexpr(std::is_arithmetic<decltype(produkt1)>{}) {
        produkt1++;
        produkt2++;
    }
    for(int i=0; i<red1.size(); i++) {
        produkt1 *= red1.at(i);
    }
    for(int i=0; i<red2.size(); i++) {
        produkt2 *= red2.at(i);
    }
    if(produkt1 == produkt2) {
        return red1 < red2;
    }
    return produkt1 < produkt2;
}

template <typename Tip>
void SortirajPoProizvoduRedova(std::vector<std::vector<Tip>> &matrica_za_sortiranje) {
    if(matrica_za_sortiranje.empty()) return;
    for(int i=0; i<matrica_za_sortiranje.size(); i++) {
        // ovdje Kriteri mozda dodat
        std::sort(matrica_za_sortiranje.begin(), matrica_za_sortiranje.end(), Kriterij<std::remove_reference_t<decltype(matrica_za_sortiranje.at(0))>>);
    }
}

int main () {
    std::cout << "Unesi elemente (* za kraj reda, * na pocetku reda za kraj unosa): ";
    std::vector<std::vector<int>> Matrica;
    for(int i=0; ; i++) {
        // brojac nam govori na kojem smo elementu, konkretno nam treba da vidimo da li smo na poz 1. elementa
        int brojac{0}, element;
        
        // indikator da nije upisan broj vec da je upisan neki znak
        bool broj_je{true};
        
        Matrica.push_back(std::vector<int>(0)); // stavljamo red
        do {
            // brisemo sve iz ulaznog toka, ako je u njemu vec nesto
            if(std::cin >> element) {
                Matrica.at(i).push_back(element);
                brojac++;
            }
            else {
                std::cin.ignore(1000, '\n');
                broj_je = false;
                break;
            }
        } while(broj_je);
        if(std::cin.peek() != '\n') {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
        if(brojac == 0 && broj_je == false) {
            // brisemo zadnji red buduci da on nema elemenata(i je kretalo od 0)
            Matrica.resize(i);
            break;
        }
        // std::cin >> std::ws;
    }

    SortirajPoProizvoduRedova(Matrica);
    std::cout << "\n" << "Matrica nakon sortiranja:" << std::endl;
    for(std::vector<int> &red : Matrica) {
        for(int &x : red) {
            std::cout << x << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\nUnesite elemente sekvence koja se trazi (* za kraj reda): ";
    std::vector<int> trazi_red;
    int element;
    while(std::cin >> element) {
        trazi_red.push_back(element);
    }
    // ulazni tok nam vise i ne treba pa ga ne moramo cistiti, ali za svaki slucaj bolje ocistiti
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    std::vector<std::vector<int>>::iterator p = std::lower_bound(Matrica.begin(), Matrica.end(), trazi_red, Kriterij<std::vector<int>>);
    if(Matrica.size() != 0) {
        if(trazi_red == *p) {
            std::cout << "Trazena sekvenca se nalazi u ";
            std::cout << (p - Matrica.begin() + 1);
            std::cout << ". redu (nakon sortiranja)";
        } else {
            std::cout << "Trazena sekvenca se ne nalazi u matrici";
        }
    } else {
        std::cout << "Trazena sekvenca se ne nalazi u matrici";
    }

	return 0;
}
