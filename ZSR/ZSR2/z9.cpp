#include <iostream>
#include <cmath>
#include <vector>

bool ParanVektor(std::vector<int> vektor) {
    for(int x : vektor) {
        if(x % 2 == 0) return true;
    }
    return false;
}

int main() {
    std::cout << "Unesite prirodan broj n: ";
    int n;
    std::cin >> n;
    std::vector<int> vektor(n);
    for(int i=0; i<n; i++) {
        int broj;
        while(!(std::cin >> broj)) {
            std::cout << "Pogresan unos!" << std::endl;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
        vektor.at(i) = broj;
    }
    std::cout << std::boolalpha << "Broj sadrzi parne brojeve? " << ParanVektor(vektor) << std::endl;
    return 0;
}