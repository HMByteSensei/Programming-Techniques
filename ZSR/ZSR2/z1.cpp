#include<iostream>
#include<cmath>

bool Palindrom(int broj) {
    int broj_cifara = log10(broj) + 1;
    bool palindrom = true;
    for(int i=0; i<=broj_cifara/2; i++) {
        int zadnja = broj % 10;
        int prva = (broj - (broj % static_cast<int>(std::pow(10, broj_cifara-1)))) / std::pow(10, broj_cifara-1);
        broj = broj % static_cast<int>(std::pow(10, (broj_cifara-1)));
        broj /= 10; //update broj
        broj_cifara -= 2;
        if(prva != zadnja) {
            palindrom = false;
            break;
        }
    }
    return palindrom;
}

int main() {
    double broj;
    do {
        std::cout << "Unesite neki cijeli broj, nulu za kraj: ";
        std::cin >> broj;
        if(broj == 0) break;
        if(std::cin.fail() || broj != static_cast<int>(broj)) {
            std::cout << "Pogresan unos!" << std::endl;
            std::cin.ignore(1000, '\n');
            std::cin.clear();
        } else std::cout << "True/False = Jeste/Nije palindrom " << std::boolalpha << Palindrom(broj) << std::endl;
    }while(true);

    return 0;
}