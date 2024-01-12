#include <iostream>
#include <cmath>
#include <vector>

std::vector<int> Vektor(int broj) {
    std::vector<int> vek;
    for(int i=1; i<(broj/2+1); i++) {        
        if(broj % i == 0) {
            vek.push_back(i);
        }
    }
    return vek;
}

int main() {
    std::cout << "Unesite broj n: ";
    int n;
    std::cin >> n; //predpostavljamo ispravan unos
    std::vector<int> vek = Vektor(n);
    for(int x : vek) std::cout << x << " ";
    std::cout << std::endl;
    return 0;
}