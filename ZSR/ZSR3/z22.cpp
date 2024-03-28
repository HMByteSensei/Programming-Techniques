#include <iostream>
#include <iomanip>

int main() {
    int m, n;
    std::cout << "Unesite koeficjente m i n: ";
    while (!(std::cin >> m >> n) || n > m)
    {
        std::cout << "Pogresan unos." << std::endl;
        std::cin.ignore(1000, '\n');
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cin.clear();
    }
    int koeficjent = n / 2;
    for(int i=0; i<n; i++){
        if(i < koeficjent) {
            std::cout << std::setw(koeficjent-i) << "" << "*" << std::setw(m-2*(koeficjent+1)+i*2) << "" 
            << "*" << std::endl;
        } else if(i > koeficjent) {
            std::cout << std::setw(i-koeficjent) << "" << "*" << std::setw((m--) - 2 - i + koeficjent) << ""
            << "*" <<  std::endl;
        } else {
            std::cout << std::setw(m) << std::setfill('*') << "" << std::endl;
            std::cout.fill(' ');
            std::cout << "";
            m--;
        }
    }
    return 0;
}