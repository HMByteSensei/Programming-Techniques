#include <iostream>

int main() {
    int broj_sati;
    std::cout << "Unesite zeljeni broj sati: ";
    std::cin >> broj_sati;
    //prva firma 10KM + (50 feninga po satu)
    double prva_firma = 10 + broj_sati * 0.5;
    //druga firma 80 feninga po satu
    double druga_firma = broj_sati * 0.8;
    std::cout << "Jeftinija je " << ( (prva_firma < druga_firma) ? "prva firma." : "druga firma.") 
    << std::endl; 
}