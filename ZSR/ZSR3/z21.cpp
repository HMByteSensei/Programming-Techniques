#include <iostream>
#include <iomanip>

int main() {
    unsigned int n; 
    std::cout << "Unesite broj n: ";
    while(!(std::cin >> n) || n > 100) { 
        std::cout << "Ponovite unos, ali ovog puta unesite poz. br." << std::endl;
        std::cin.clear();
        std::cin.ignore(1000, '\n');
    }
    std::cout << std::setw(n) << "*" << std::endl;
    for(int i=1; i<n; i++) {
        if(i == (n - 1) ) {
            std::cout << std::setw(n*2-1) << std::setfill('*') << "" << std::endl;
        } else {
            std::cout << std::setw(n-i-1) << std::setfill(' ') << "" << std::setw(1) << "*" 
            << std::setw(i*2-1) << std::setfill(' ') << "" << "*" << std::endl; 
        }
    }
    return 0;
}