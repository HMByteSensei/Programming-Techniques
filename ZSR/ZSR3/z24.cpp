#include <iostream>
#include <iomanip>

void Ispis(int m) {
    std::cout << std::setw(m) << std::setfill('*') << "" << std::endl;
    std::cout.fill(' ');
}

int main() {
    std::cout << "Unesite cijele brojeve m i n: ";
    int m, n;
    while(!(std::cin >> m >> n) || m<n) {//predpostavljamo da ce biti pozitivni brojevi
        std::cout << "Pogresan unos!" << std::endl;
        if(std::cin.fail()) {
            std::cin.ignore(1000, '\n');
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cin.clear();
        }
    }
    Ispis(m);
    for(int i=0; i<n-2; i++) {
        if(i<=((n-2)/2)) {  
            std::cout << std::setw(i+1) << "" << "*" << std::setw(m-2*i-4) << "" << "*" << std::endl;
        } else {
            std::cout << std::setw(n-i-1) << "*" << std::setw(m - 2*(n-i-2)-1) << "*" << std::endl;
        }
    }
    Ispis(m);
    return 0;
}