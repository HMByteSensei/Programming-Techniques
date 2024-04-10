#include <iostream>

double stepen(int x, int n) {
    double rezultat = 1;
    if(n>0) {
        for(int i=0; i<n; i++) {
            rezultat = rezultat * x;
        }
    }
    else {
        for(int i=0; i>n; i--) {
            rezultat = rezultat*x;    
        }
        rezultat = 1./rezultat;
    }
    return rezultat;
}

int main() {
    std::cout << stepen(2, 5) << std::endl;
    std::cout << stepen(10, -3) << std::endl;  
    std::cout << stepen(4, 2) << std::endl;
    return 0;
}