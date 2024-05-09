#include <iostream>
#include <cmath>
#include <complex>

int main () {
    std::cout << "Unesite broj elemenata: ";
    int n;
    std::cin >> n;
    std::complex<double> impedansa{};

    const double PI = 4*atan(1);
    for(int i=0; i<n; i++) {
        std::cout << "\nZ" << i+1 << " = ";
        double Z;
        std::cin >> Z;
        std::cout << "fi" << i+1 << " = ";
        double fi;
        std::cin >> fi;
        impedansa += 1./std::polar(Z, fi*PI/180);
    }
    // Autor: Muhamed Husić
    std::cout << std::endl << "Paralelna veza ovih elemenata ima Z = " 
    << std::abs(1./impedansa) << " i fi = " << std::arg(1./impedansa)*180/PI << "." << std::endl;
    return 0;
}