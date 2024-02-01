#include <iostream>
#include <vector>
#include <cmath>

std::vector<int> PerfektanBroj(std::vector<int> vektor) {
    std::vector<int> rezultat;
    for(int i=0; i<vektor.size(); i++) {
        int suma{0};
        for(int j=1; j<(vektor.at(i)/2 + 1); j++) { //j=1 jer ne mozemo dijeliti s nulom
            if((vektor.at(i) % j) == 0) {
                suma += j;
            }
        }
        if(suma == vektor.at(i)) rezultat.push_back(suma);
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
    std::vector<int> rez = PerfektanBroj(vektor);
    for(int x : rez) std::cout << x << " ";
    std::cout << std::endl;
    return 0;
}