#include <iostream>
#include <vector>
#include <cmath>

bool Oscilatoran(std::vector<int> vektor) {
    bool povecavajuci = true;
    if(vektor.at(1) < vektor.at(0) ) {
        povecavajuci = false;
    }
    bool oscilatoran = true;
    for(int i=1; i<(vektor.size()-1); i++) {
        if(povecavajuci && vektor.at(i+1) < vektor.at(i)) {
            oscilatoran = false;
        }
        if(!povecavajuci && vektor.at(i+1) > vektor.at(i)) {
            oscilatoran = false;
        }
    }
    return oscilatoran;
}
int main() {
    std::cout << "Unesite n: ";
    int n;
    std::cin >> n;
    std::vector<int> vektor(n);
    for(int i=0; i<n; i++) {
        while(!(std::cin >> vektor.at(i))){
            std::cout << "Pogresan unos!\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
    }
    std::cout << "Vektor jese/nije oscilatoran? (true/false) " << std::boolalpha 
    << Oscilatoran(vektor) << std::endl;
    return 0;
}