#include <iostream>

int main() {
    std::cout << "Unesite neki broj: ";
    double x;
    std::cin >> x;
    if(!std::cin)
    {
        std::cout << "Uneseni podatak nije broj." << std::endl;
    }
    else if(static_cast<int>(x) == x && x < 0) {
        std::cout << "Uneseni podatak je cijeli broj, ali nije prirodan." << std::endl;
    }
    else if(static_cast<int>(x) != x) {
        std::cout << "Uneseni podatak je realan broj, ali nije cijeli." << std::endl;
    }
    else {   
        std::cout << "Uneseni podatak je prirodan broj." << std::endl;
    }
    return 0;
}