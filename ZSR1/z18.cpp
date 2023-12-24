#include <iostream>
#include <iomanip>

void Ispisi(int n) {    
    for(int i=0; i<n; i++) {
        std::cout << "+" << std::setw(5) << std::setfill('-') << "";
    }
    std::cout << "+" << std::endl;
    std::cout.fill(' ');
}
int main() {
    std::cout << "Unesite prirodan broj n: ";
    int n;
    std::cin >> n;
    Ispisi(n);  
    for(int i=1; i<=n; i++) {
        std::cout << "|";
        for(int j=1; j<=n; j++) {
            std::cout << std::setw(4) << (i * j) << " |";
        }
        std::cout << std::endl;
        Ispisi(n);
    }
    return 0;
}