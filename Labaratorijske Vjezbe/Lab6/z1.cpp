#include <exception>
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <limits>

template <typename Tip>
Tip *GenerirajStepeneDvojke(int n) {
    if(n <= 0) {
        throw std::domain_error("Broj elemenata mora biti pozitivan");
    }
    Tip *pok{};
    try {
        pok = new Tip[n];
    } catch(...) {
        throw std::runtime_error("Alokacija nije uspjela");
    }
    try {
        Tip broj{1};
        for(int i=0; i<n; i++) {
            //zasto funkcija pow pravi problem tj. ovo ne radi padaju 3 8 i 9 testovi ako je if:
            //if(i != n-1 && static_cast<Tip>(std::pow(2, i)) > std::numeric_limits<Tip>::max())  
            
            // a ako je ovako samo 8 test pada, sto se mora dijelit s dva
            // if((std::pow(2, i)) > std::numeric_limits<Tip>::max()) 
            //     throw std::overflow_error("");
            if(i != n-1 && broj > std::numeric_limits<Tip>::max()/2) 
                throw std::overflow_error("");
            //pok[i] = std::pow(2, i);
            pok[i] = broj;
            broj *= 2;
        }
    } catch(...) {
        delete[] pok;
        throw std::overflow_error("Prekoracen dozvoljeni opseg");
    }
    return pok;
}

int main ()
{
    std::cout << "Koliko zelite elemenata: ";
    int n;
    std::cin >> n;
    try {
        unsigned long long *a = GenerirajStepeneDvojke<unsigned long long>(n);
        for(int i=0; i<n; i++) {
            std::cout << a[i] << " ";
        }
        delete[] a;
    } catch(std::exception &e) {
        std::cout << "Izuzetak: " << e.what();
    }

	return 0;
}
