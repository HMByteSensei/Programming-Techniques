#include <iostream>
#include <cmath>

int brojac = 1; //na liniji 18, 20 i 32

int MultOtpornost(int broj) {
    int rezultat = 1;
    while(true) {
        if(broj == 0) break;
        int cifra = broj % 10;
        broj /= 10;
        rezultat *= cifra;
    }
    //std::cout << "Rez: " << rezultat << std::endl;
    if(rezultat < 10) {
        //std::cout << "Ret brojac..." << std::endl;
        return brojac;
    } else {
        brojac++;
        //std::cout << "Brojac++" << std::endl;
        return MultOtpornost(rezultat);
    }
    return 1; //zbog kompajlera
}

int main() {
    std::cout << "Unesite koeficjente a, b i k pri cemu k predstavlja multiplikatornu otpornist: ";
    int a, b, k;
    std::cin >> a >> b >> k;
    for(; a <= b; a++) {
        brojac = 1;
        if(MultOtpornost(a) == k) {
            std::cout << a << " ";
        }
    }
    //std::cout << MultOtpornost(a) << std::endl;
    return 0;
}