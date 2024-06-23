#include <iostream>
#include <cmath>
#include <new>
#include <stdexcept>
#include <algorithm>

int **KreirajTrougao(int n) {
    if(n <= 0) {
        throw std::domain_error("Broj redova mora biti pozitivan");
    }
    int **niz_pokazivaca_na_nizove = new int*[n];
    // try {
    //     niz_pokazivaca_na_nizove = new int*[n];
    // } catch(std::bad_alloc) {
    // }
    // treba try-catch jer moze da ne uspije npr 10 element da se dinamicki alocira
    int brojac_uspjesno_alociranih{};
    try {
        *(niz_pokazivaca_na_nizove) = new int[1];
        **niz_pokazivaca_na_nizove = 1;
        brojac_uspjesno_alociranih++;
        for(int i=1; i<n; i++) {
            *(niz_pokazivaca_na_nizove + i) = new int[i*2+1];
            brojac_uspjesno_alociranih++;
	    // Autor: Muhamed Husić
            for(int j=0; j<i+1; j++) {
                niz_pokazivaca_na_nizove[i][j] = i+1-j;
            }
            int br{2};
            for(int j=i+1; j<=i*2; j++) {
                niz_pokazivaca_na_nizove[i][j] = br++;
            }
            // zasto ne moze copy kada ona moze primati pokazivace
            //std::copy(niz_pokazivaca_na_nizove[i][0], niz_pokazivaca_na_nizove[i][(i*2)/2+1], niz_pokazivaca_na_nizove[i][(i*2)/2 + 2]);
            // zato sto mu je poslat [i][0] a to je samo dio niza tj to je jedan znak, a copy zahtijeva cio niz
        }
    } catch(std::bad_alloc) {
        for(int i=0; i<brojac_uspjesno_alociranih; i++) {
            delete[] niz_pokazivaca_na_nizove[i];
        }
        delete[] niz_pokazivaca_na_nizove;
        throw;
    }
    return niz_pokazivaca_na_nizove;
}

int main () {
    std::cout << "Koliko zelite redova: ";
    int n;
    std::cin >> n;
    try {
        int **trougao = KreirajTrougao(n);
        for(int i=0; i<n; i++) {
            for(int j=0; j<i*2+1; j++) {
                std::cout << trougao[i][j] << " ";
            }
            std::cout << std::endl;
        }
        for(int i=0; i<n; i++) {
            delete[] trougao[i];
        }
        delete[] trougao;
    }
    catch(std::domain_error e) {
        std::cout << "Izuzetak: Broj redova mora biti pozitivan" << std::endl;
    }
    catch(std::bad_alloc&) {
        std::cout << "Izuzetak: Nedovoljno memorije!" << std::endl;
    }
	return 0;
}
