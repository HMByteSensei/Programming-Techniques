#include <iostream>
#include <cmath>
#include <vector>

bool StepenBrojaDva(std::vector<int> vektor) {
    std::cout << "\n";
    for(int x:vektor) std::cout << x << "\t";
    std::cout << "\n";
    for(int i=0; i<vektor.size(); i++) {
        if(vektor.at(i) > 0 && static_cast<int>(log2(vektor.at(i))) == log2(vektor.at(i))) {
            return true;
        }
        std::cout << vektor.at(i) << "\t";
        std::cout << log2(vektor.at(i)) << "\t";
        std::cout << static_cast<int>(log2(vektor.at(i))) << ";;;\t";
    }
    std::cout << "\n";
    return false;
}


int main() {
    std::cout << "Unesite prirodan broj n: ";
    int n;
    std::cin >> n; //predpostavljamo ispravan unos
    std::vector<int> vektor;
    std::cout << "Unesite elemente: \n";
    for(int i=0; i<n; i++) {
        int element;
        std::cin >> element;
        vektor.push_back(element);
    }
    //for(int x:vektor) std::cout << x << "\t";
    //std::cout << "\n";
    std::cout << "Vektor sadrzi broj koji je stepena broja 2? (true/false) " 
    << std::boolalpha << StepenBrojaDva(vektor) << std::endl;
    return 0;
}