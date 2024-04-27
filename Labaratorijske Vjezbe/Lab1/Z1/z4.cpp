#include <iostream>
#include <cmath>
int main () {
    do {
        std::cout << "Unesite prirodan broj ili 0 za kraj: ";
        double broj;
        std::cin >> broj;
        if(std::cin.fail() || broj < 0 || broj != static_cast<int>(broj)) {
            std::cout << "Niste unijeli prirodan broj!" << std::endl;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        } else if(static_cast<int>(broj)==broj && (broj == 0)){
            std::cout << "Dovidjenja!" << std::endl;
            break;
        } else {
            int suma = 0;
            for(int i=1; i<(std::floor(broj/2) + 1); i++) {
                if((static_cast<int>(broj) % i) == 0) {
                    //std::cout << "U if " << i << "\t";
                    suma += i;
                }
            }
            if(suma < broj) {
                std::cout << "Broj " << broj << " je manjkav!" << std::endl;
            } else if(broj == suma) {
                std::cout << "Broj " << broj << " je savrsen!" << std::endl;
            } else {
                std::cout << "Broj " << broj << " je obilan!" << std::endl;
            }
        }
    }while(true);
	return 0;
}