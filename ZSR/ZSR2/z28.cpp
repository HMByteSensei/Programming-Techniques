#include <iostream>
#include <vector>
#include <cmath>

std::vector<bool> ProstBroj(std::vector<int> vektor) {
    std::vector<bool> rezultat(vektor.size());
    for(int i=0; i<vektor.size(); i++) {
        bool prost = true;
        for(int j=2; j<(vektor.at(i)/2 + 1); j++) {
            if((vektor.at(i) % j) == 0) {
                prost = false;
            }
        }
        rezultat.at(i) = prost;
    }
    return rezultat;
}
int main() {
    std::cout << "Unesite n: ";
    int n;
    std::cin >> n;
    std::vector<int> vektor(n);
    for(int i=0; i<n; i++) {
        while(!(std::cin >> vektor.at(i))){
            std::cout << "Pogresan unos!\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
    }
    std::vector<bool> rez = ProstBroj(vektor);
    for(bool x : rez) std::cout << std::boolalpha << x << " ";
    std::cout << std::endl;
    return 0;
}