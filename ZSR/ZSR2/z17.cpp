#include <iostream>
#include <vector>
#include <cmath>

std::vector<int> Djeljiv(int broj) {
    std::vector<int> rezultat;
    for(int i=100; i<1000; i++) {
        if(i%broj == 0) {
            rezultat.push_back(i);
        }
    }
    return rezultat;
}

int main() {
    std::cout << "Unesite broj: ";
    int n;
    std::cin >> n;
    std::cout << "Dati vektor glasi: " << std::endl;
    std::vector<int> vektor = Djeljiv(n);
    for(int x : vektor) std::cout << x << "\t";
    std::cout << std::endl;
    return 0;
}