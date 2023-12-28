#include <iostream>
#include <iomanip>

int main() {
    unsigned int n;
    std::cout << "Unesite prirodan broj n: ";
    while(!(std::cin >> n)) {
        std::cout << "Pogresan unos." << std::endl;
        std::cin.ignore(1000, '\n');
        std::cin.clear();
    }
    //std::cout << std::setw(n) << "*" << std::endl;
    for(int i=0; i<n; i++) {
        std::cout << std::setw(n-i-1) << std::setfill(' ') << "" << std::setw(i*2+1) 
        << std::setfill('*') << "" << std::endl;
    }
    return 0;
}