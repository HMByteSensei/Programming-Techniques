#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

std::vector<std::vector<int>> PascalovTrougao(int n) {
    if(n < 0) 
        throw std::domain_error("Broj redova ne smije biti negativan");
    std::vector<std::vector<int>> trougao(n);
    for(int i=0; i<n; i++) {
        for(int j=0; j<i+1; j++) {
            if(j==0 || j==i) {
                trougao.at(i).push_back(1);
            } else {
                trougao.at(i).push_back(trougao.at(i-1).at(j) + trougao.at(i-1).at(j-1));
            }
        }
    }
    return trougao;
}

int NajvecaSirina(std::vector<std::vector<int>> matrica_c) {
    int najvise_cifri{0};
    for(std::vector<int> red : matrica_c) {
        for(int x : red) {
            int broj_cifri = log10(std::fabs(x)) + 1;
            if(najvise_cifri < broj_cifri) {
                najvise_cifri = broj_cifri;
            }
        }
    }
    return najvise_cifri + 1;
}

int main ()
{
    std::cout << "Unesite broj redova: ";
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> matrica{PascalovTrougao(n)};
    int sirina{NajvecaSirina(matrica)};
    for(std::vector<int> red : matrica) {
        for(int x : red) {
            std::cout << std::setw(sirina) << x;
        }
        std::cout << std::endl;
    }
	return 0;
}
