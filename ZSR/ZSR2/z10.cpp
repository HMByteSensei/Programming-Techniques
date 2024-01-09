#include <iostream>
#include <cmath>
#include <vector>

bool PotpunKvadrat(std::vector<double> vektor) {
    for(double x : vektor) {
        if(std::sqrt(x) == static_cast<int>(std::sqrt(x))) { 
            return true;
        }
    }
    return false;
}

int main() {
    std::cout << "Unesite prirodan broj n: ";
    int n;
    std::cin >> n;
    std::vector<double> vektor(n);
    for(int i=0; i<n; i++) {
        double broj;
        while(!(std::cin >> broj)) {
            std::cout << "Pogresan unos!" << std::endl;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
        vektor.at(i) = broj;
    }
    std::cout << std::boolalpha << "Broj sadrzi potpune kvadrate? " << PotpunKvadrat(vektor) << std::endl;
    return 0;
}