#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

typedef std::vector<int> VECTOR;

std::vector<std::vector<int>>KroneckerovProizvod(VECTOR a, VECTOR b) {
    std::vector<std::vector<int>> rezultat(a.size(), VECTOR(b.size()));
    for(int i=0; i<a.size(); i++) {
        for(int j=0; j<b.size(); j++) {
            rezultat.at(i).at(j) = a.at(i) * b.at(j);
        }
    }
    return rezultat;
}

int NajvecaSirina(std::vector<VECTOR> matrica_c) {
    int najvise_cifri{0};
    bool neg_br;
    for(std::vector<int> red : matrica_c) {
        for(int x : red) {
            int broj_cifri = log10(std::fabs(x)) + 1;
            if(x<0) broj_cifri++;
            if(najvise_cifri < broj_cifri) {
                najvise_cifri = broj_cifri;
                if(x < 0) neg_br = true;
                else neg_br = false;
            }
        }
    }
    return najvise_cifri;
}

std::vector<int> Unesi(std::vector<int> vec, int br) {
    for(int i=0; i<br; i++) {
        std::cin >> vec.at(i);
    }
    return vec;
}

int main ()
{
    std::cout << "Unesite broj elemenata prvog vektora: ";
    int broj1;
    std::cin >> broj1;
    std::cout << "Unesite elemente prvog vektora: ";
    std::vector<int> vektor1(broj1);
    vektor1 = Unesi(vektor1, broj1);
    
    std::cout << "Unesite broj elemenata drugog vektora: ";
    int broj2;
    std::cin >> broj2;
    std::cout << "Unesite elemente drugog vektora:";
    std::vector<int> vektor2(broj2);
    vektor2 = Unesi(vektor2, broj2);

    std::vector<std::vector<int>> matrica_c;
    matrica_c = KroneckerovProizvod(vektor1, vektor2);
	std::cout << std::endl;
    int sirina = NajvecaSirina(matrica_c);
    for(std::vector<int> red : matrica_c) {
        for(int x : red) {
            std::cout << std::right << std::setw(sirina+1) << x;
        }
        std::cout << std::endl;
    }
    return 0;
}
