#include <iostream>
#include <iomanip>

int main () {
    unsigned int n, m;
    std::cout << "Unesite n i m: ";
    while (!(std::cin >> n >> m)) {
        std::cout << "Pogresan unos." << std::endl;
        std::cin.ignore(1000, '\n');
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cin.clear();
    }
    if(std::cin.fail()) {
        std::cout << "Pogresan unos" << std::endl;
        std::exit(0);
    }
    for(int i=0; i<m; i++) {
        if(i==0 || i==(m-1)) {
            std::cout << std::setw(n) << std::setfill('*') << "" << std::endl;
        } else {
            std::cout << "*" << std::setw(n-1) << std::setfill(' ') << "*" << std::endl;
        }
    }
    return 0;
}