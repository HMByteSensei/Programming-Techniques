#include <iostream>
#include <cmath>
#include <type_traits>
#include <vector>
#include <deque>

template <typename Matrica>
auto KreirajDinamickuKopiju2D(Matrica matrica) -> typename std::remove_reference<decltype(matrica.at(0).at(0))>::type**{
    // ako ovo ne uspije dolazi do bacanja izuzetka, pa se prekida f-ija
    std::remove_reference_t<decltype(matrica.at(0).at(0))>** kopija = new 
    std::remove_reference_t<decltype(matrica.at(0).at(0))>*[matrica.size()]{};
    // moze biti grbava matrica
    int broj_elemenata{};
    for( std::remove_reference_t<decltype(matrica.at(0))> &x : matrica) {
        for(std::remove_reference_t<decltype(matrica.at(0).at(0))> &y : x )
            broj_elemenata++;
    }
    try {
        kopija[0] = new std::remove_reference_t<decltype(matrica.at(0).at(0))>[broj_elemenata];
        for(int i=1; i<matrica.size(); i++) {
            kopija[i] = kopija[i-1] + matrica.at(i-1).size();
        }
    } catch(std::bad_alloc) {
        delete[] kopija[0];
        delete[] kopija;
        throw;
    }
    for(int i=0; i<matrica.size(); i++) {
        for(int j=0; j<matrica.at(i).size(); j++) {
            kopija[i][j] = matrica.at(i).at(j);
        }
    }
    return kopija;
}

int main ()
{
    std::cout << "Unesite broj redova kvadratne matrice: ";
    int n;
    std::cin >> n;
    std::vector<std::deque<int>> m;
    try {
        m.resize(n);
        for(int i=0; i<n; i++) {
            m.at(i).resize(n);
        }
    } catch(std::bad_alloc&) {
        std::cout << "Nedovoljno memorije\n";
        return 0;
    }
    std::cout << "Unesite elemente matrice: ";
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            std::cin >> m.at(i).at(j);
        }
    }
    int **p = nullptr;
    try {
        p = KreirajDinamickuKopiju2D(m);
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                std::cout << *(*(p+i) + j) << " ";
                //std::cout << p[i][j] << " ";
            }
            std::cout << "\n";
        }
        delete[] p[0];
        delete[] p;
    }
    catch(std::bad_alloc) {
        delete[] p;
        std::cout << "Nedovoljno memorije";
    }
	return 0;
}