#include <iostream>
#include <iomanip>

int main() {
    std::cout << "Unesite koeficjente m i n: ";
    int m, n;
    while(!(std::cin >> m >> n) || n > m  || n < 0 || m < 0) {
        if(std::cin.fail()) {
            std::cin.ignore(1000, '\n');
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cin.clear();
        }
        std::cout << "Ponovite unos!" << std::endl;
    }
    for(int i=0; i<n; i++) {
        if(i<n/2) {
            std::cout << std::right << std::setw(i+1) << "*"  << std::setw(m-2*i-1) 
            << "*" << std::endl; 
        }
        else if(i == n/2) {
            std::cout << std::setw(n/2) << "" << std::setw(m - 2*(n/2)) << std::setfill('*') 
            << "" <<std::endl;
            std::cout.fill(' ');
        }
        else {
            std::cout << std::right << std::setw(n-i) << "*" << std::left << std::setw(m-2*(n-i)) 
            << "" << "*" << std::endl;
        }
    }
    return 0;
}