//TP 2022/2023: Zadaća 2, Zadatak 5
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <typeinfo>
#include <complex>
#include <vector>
#include <deque>
#include <list>
#include <array>

template <typename IterTip1, typename IterTip2>
auto KreirajTablicuSabiranja(IterTip1 pok1_na_a, IterTip1 pok2_na_a, IterTip2 pok_na_b) -> std::remove_reference_t<decltype(*pok1_na_a + *pok_na_b)>** {

    IterTip1 temp = pok1_na_a;
    int broj_elemenata{};
    while(temp++ != pok2_na_a) {
        broj_elemenata++;
    }
    std::remove_reference_t<decltype(*pok1_na_a + *pok_na_b)> **matrica = nullptr;
    try {
        matrica = new std::remove_reference_t<decltype(*pok1_na_a + *pok_na_b)> *[broj_elemenata];
        matrica[0] = new std::remove_reference_t<decltype(*pok1_na_a + *pok_na_b)>[broj_elemenata * (broj_elemenata + 1) / 2]{};
    } catch(...) {
        delete[] matrica;
        throw std::range_error("Nema dovoljno memorije!");
    }
    int index{};
    for(int i=0; i<broj_elemenata; i++) {
        if(i != 0) {
            matrica[i] = matrica[i-1] + i;
        }
        //auto temp_a = pok1_na_a;
        auto temp_b = pok_na_b;
        for(int j=0; j<=i; j++) {
            auto zbir = *pok1_na_a + *pok_na_b;
            if(zbir != (*pok_na_b + *pok1_na_a)) {
                delete[] matrica[0];
                delete[] matrica;
                throw std::logic_error("Nije ispunjena pretpostavka o komutativnosti");
            }
            //std::cout << "\nindex: "<<index << "\n";
            matrica[i][j] = *pok1_na_a + *temp_b;
            //std::cout << "\t" << *pok1_na_a << "\t" << *temp_b << "\t[index][j]: " << index << "   "<< j << "\tpoka+pokb: " << (*pok1_na_a + *temp_b) << "\n";
            //temp_a++;
            temp_b++;
        }
        pok1_na_a++;
    }
    return matrica;
}

int main () {
    std::cout << "Duzina sekvenci: ";
    int duzina;
    std::cin >> duzina;
    std::cout << "Elementi prve sekvence: ";
    std::vector<double> vektor(duzina);
    for(int i=0; i<duzina; i++) {
        std::cin >> vektor.at(i);
    }
    std::cout << "Elementi druge sekvence: ";
    std::deque<double> dek(duzina);
    for(int i=0; i<duzina; i++) {
        std::cin >> dek.at(i);
    }
    try {
        auto matrica = KreirajTablicuSabiranja(vektor.begin(), vektor.end(), dek.begin());
        std::cout << "Tablica sabiranja:" << std::endl;
        for(int i=0; i<duzina; i++) {
            for(int j=0; j<i+1; j++) {
                std::cout << matrica[i][j] << " ";
            }
            std::cout << std::endl;
        }
        delete[] matrica[0];
        delete[] matrica;
    } catch(std::range_error &e) {
        std::cout << e.what() << std::endl;
    } catch(std::logic_error &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}