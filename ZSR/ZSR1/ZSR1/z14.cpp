#include <iostream>
#include <cmath>

int main() {
    std::cout << "Unesite zeljeni broj: ";
    int broj;
    std::cin >> broj;
    int broj_cifara = log10(broj) + 1;
    
    int polindrom = 1; //predpostavljamo da broj jeste polindrom
    for(int i=0; i < broj_cifara/2; i++) {
        int stepen = std::pow(10, (broj_cifara - 1));
        int posljednja_cifra = broj % 10;
        int prva_cifra = (broj - (broj % stepen)) / std::pow(10, (broj_cifara - 1));
        broj = broj % stepen;
        broj /= 10;
        broj_cifara -= 2;
        if( posljednja_cifra != prva_cifra ) {
            polindrom = 0;
            break;
        }
    }
    if(polindrom) {
        std::cout << "Ovaj broj jeste polindrom." << std::endl;
    } else {
        std::cout << "Ovaj broj nije polindrom." << std::endl;
    }
    return 0;
}