#include <iostream>
#include <iomanip>

int main() {
    std::cout << "Unesite glavnicu, a potom kamatnu stopu: ";
    int glavnica, k_stopa;
    std::cin >> glavnica >> k_stopa;
    std::cout << "Glavnica:" << std::setw(12) << glavnica << std::endl << "Kamatna stopa:" 
    << std::setw(7) << k_stopa << std::endl << "Kamate:" << std::setw(14) << glavnica * k_stopa / 100 
    << std::endl << "Nova svota:" << std::setw(10) << glavnica + (glavnica * k_stopa / 100) << std::endl;
}