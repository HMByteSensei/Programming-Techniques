#include <iostream>
#include <cmath>
#include <complex>

int main () {
    std::cout << "Unesite broj elemenata: ";
    int n;
    std::cin >> n;
    std::complex<double> impedansa{};

    for(int i=0; i<n; i++) {
        std::cout << "\nR" << i+1 << " = ";
        double R;
        std::cin >> R;
        std::cout << "X" << i+1 << " = ";
        double X;
        std::cin >> X;
        std::complex<double> z{R, X};
        impedansa += 1./z;
    }
    std::cout << std::endl << "Paralelna veza ovih elemenata ima R = " 
    << std::real(1./impedansa) << " i X = " << std::imag(1./impedansa) 
    << "." << std::endl;
    return 0;
}
