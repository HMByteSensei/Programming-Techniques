#include<iostream>
#include<cmath>

bool SadrziJednakehCifre(int broj) {
    int broj_cifri = (log10(broj) + 1);
    for(int i=0; i<broj_cifri; i++) {
        int temp = broj % 10;
        broj /= 10;
        int kopija_broja = broj;
        broj_cifri--;
        for(int j=0; j<broj_cifri; j++){
            if(temp == (kopija_broja % 10)) {
                return true;
            }
            kopija_broja /= 10;
        }
    }
    return false;
}

int main() {
    std::cout << "Unesi prirodan broj: ";
    int broj;
    std::cin >> broj;
    std::cout << "Broj sadrzi isti broj cifri. " << std::boolalpha << SadrziJednakehCifre(broj) << std::endl;
    return 0;
}