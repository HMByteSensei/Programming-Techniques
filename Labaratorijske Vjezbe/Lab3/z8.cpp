#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>
// Husić Muhamed
std::string IzdvojiRijec(std::string recenica, int broj) {
    int brojac{1}, i{0};
    while(i < recenica.length() && (recenica.at(i) == ' ' || recenica.at(i) == '\t')) {
        i++;
    }
    if(i == recenica.length()) {
        --brojac;
    }
    while(i < recenica.length() && broj != brojac) {
        while(i < recenica.length() && recenica.at(i) != ' ') {
            i++;
        }
        while(i < recenica.length() && recenica.at(i) == ' ') {
            i++;
        }
        if(i<recenica.length()) brojac++;
    }
    // brojac je pocetni indeks rijeci na poziciji broj
    int poc{i};
    //i ce biti krajnji indeks
    while(i < recenica.length() && recenica.at(i) != ' ') {
        i++;
    }
    if(broj < 1 || brojac < broj) {
        throw std::range_error("Pogresan redni broj rijeci!");
    }
    return recenica.substr(poc, i-poc);
}

int main ()
{
    std::cout << "Unesite redni broj rijeci: ";
    int n;
    std::cin >> n;
    std::cin.ignore(1000, '\n');
    std::cout << "Unesite recenicu: ";
    std::string recenica;
    std::getline(std::cin, recenica);
    try {
        if(IzdvojiRijec(recenica, n).empty());
        std::cout << "Rijec na poziciji " << n << " je " 
        << IzdvojiRijec(recenica, n) << std::endl;
    } catch(std::range_error e) {
        std::cout << "IZUZETAK: " << e.what() << std::endl;
    }
	return 0;
}
