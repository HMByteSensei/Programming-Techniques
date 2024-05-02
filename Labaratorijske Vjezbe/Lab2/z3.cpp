#include <iostream>
#include <cmath>
#include <complex>
// Autor: Muhamed Husić
int main () {
    std::cout << "Unesite broj elemenata: ";
    int n;
    std::cin >> n;
    std::complex<double> impedansa{};
    for(int i=0; i<n; i++) {
        std::complex<double> z;
        std::cout << "\nZ_" << i+1 << " = ";
        std::cin >> z;
        impedansa += 1./z;
    }
    std::cout << std::endl << "Paralelna veza ovih elemenata ima impedansu Z_ = " << 1./impedansa << "." << std::endl;
	return 0;
}
