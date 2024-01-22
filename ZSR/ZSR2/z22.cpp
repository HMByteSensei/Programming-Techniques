#include <iostream>
#include <vector>
#include <cmath>

std::vector<int> VektorProstihBrojeva(int n) {
    int brojac = log10(n);
    std::vector<int> rezultat(brojac+1);
    while(n != 0) {
        int provjeravana_cifra = n % 10;
        n /= 10;
        bool prost=true;
        for(int j=2; j<(provjeravana_cifra/2 + 1); j++) {
            if((provjeravana_cifra % j) == 0) {
                prost = false;
                break;
            }
        }
        
        if(prost && provjeravana_cifra != 0) {
            rezultat.at(brojac) = provjeravana_cifra;
            brojac--;
        } 
    }
    return rezultat;
}

int main() {
    std::cout << "Unesite neki broj: ";
    int n;
    std::cin >> n;
    std::cout << "Trazeni vektor je: " << std::endl;
    std::vector<int> v = VektorProstihBrojeva(n);
    for(int x : v) std::cout << x << " ";
    std::cout << std::endl;
    return 0;
}