#include <iostream>
#include <cmath>
#include <string>

template <typename Tip>
void UnosBroja(std::string prompt, std::string greska, Tip &broj) {
    bool unesen{false};
    do {
        std::cout << prompt;
        if(!(std::cin >> broj) || std::cin.peek() != '\n') {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << greska << std::endl;;
        } else {
            unesen = true;
        }
    }while(!unesen);
}

int main ()
{
    double x;
    int n;
    UnosBroja("Unesite bazu: ", "Neispravan unos, pokusajte ponovo...", x);
    UnosBroja("Unesite cjelobrojni eksponent: ", "Neispravan unos, pokusajte ponovo...", n);
    std::cout << x;
    // Autor: Muhamed Husic
    double rezultat{x};
    for(int i=1; i<std::fabs(n); i++) {
        rezultat *= x;
    }
    x = rezultat;
    if(n<0) {
        x = 1/x;
    } else if(n==0) {
        x=1;
    }
    std::cout << " na " << n << " iznosi " << x;
	return 0;
}
