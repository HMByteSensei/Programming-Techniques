//TP 2022/2023: Zadaća 2, Zadatak 3
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <complex>
#include <type_traits>
#include <iomanip>

template <typename TipElemenataMatrice>
using Matrica = std::vector<std::vector<TipElemenataMatrice>>;

//-> Matrica<decltype(f(TipA{}, TipB{}))> 

template <typename TipA, typename TipB, typename PovratniF, typename PovratniG>
auto GeneraliziraniMatricniProizvod(Matrica<TipA> matA, Matrica<TipB> matB, PovratniF f, PovratniG g ) {
    //auto proiz = g(TipA{}, TipB{});

    for(int i=0; i<matA.size(); i++) {
        if(matA.at(i).size() != matB.size()) {
                throw std::domain_error("Matrice nisu saglasne za mnozenje");
        }
    }
    using TIP = decltype(f(g(TipA{}, TipB{}), g(TipA{}, TipB{})));
    if(matA.size() == 0 || matB.size() == 0) {
        return Matrica<TIP>{};
    }

    int n = matA.at(0).size(), p = matB.at(0).size(), m = matA.size();
    Matrica<TIP> rezultat(m, std::vector<TIP>(p));
    try {
        for(int k=0; k<m; k++) {
            //rezultat.push_back(std::vector<decltype(f(g(TipA{}, TipB{}), g(TipA{}, TipB{})))>{});
            for(int i=0; i<p; i++) {
                auto element = g(matA.at(k).at(0), matB.at(0).at(i));
                for(int j=1; j<n; j++) {
                    element = f(element, g(matA.at(k).at(j), matB.at(j).at(i)));
                    //produkt = g(matA.at(k).at(j), matB.at(j).at(i));
                }
                rezultat.at(k).at(i) = element;
            }
        }
    } catch(...) {
        throw std::runtime_error("Neocekivani problemi pri racunanju");
    }
    return rezultat;
}

int main ()
{
    std::cout << "Unesite broj redova prve matrice: ";
    int m;
    std::cin >> m;
    std::cout << "Unesite broj kolona prve matrice, ujedno broj redova druge matrice: ";
    int n;
    std::cin >> n;
    std::cout << "Unesite broj kolona druge matrice: ";
    int p;
    std::cin >> p;

    Matrica<std::string> vA(m, std::vector<std::string>(n));
    std::cout << "Unesite elemente prve matrice: " << std::endl;
    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            std::cin >> vA.at(i).at(j);
        }
    }
    Matrica<std::string> vB(n, std::vector<std::string>(p));
    std::cout << "Unesite elemente druge matrice: " << std::endl;
    for(int i=0; i<n; i++) {
        for(int j=0; j<p; j++) {
            std::cin >> vB.at(i).at(j);
        }
    }
    try {
        auto GMP = GeneraliziraniMatricniProizvod(vA, vB, [](std::string x, std::string y) {
            return x + "+" + y;
        }, [](std::string x, std::string y) {
            return x + "*" + y;
        });
        std::cout << "\nMatricni proizvod:\n";
        for(auto x : GMP) {
            for(auto y : x) {
                std::cout << y << " ";
            }
            std::cout << "\n";
        }
    } catch(std::runtime_error e) {
        std::cout << e.what() << std::endl;
    } catch(std::domain_error e) {
        std::cout << e.what() << std::endl;
    }
	return 0;
}