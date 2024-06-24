#include <iostream>
#include <cmath>
#include <new>
#include <stdexcept>
#include <algorithm>

int **KreirajTrougao(int n) {
    if(n <= 0) {
        throw std::domain_error("Broj redova mora biti pozitivan");
    }
    // n^2 je ukupan broj elemenata
    int **niz_pokazivaca_na_nizove = new int*[n]{};
    // ne treba try block, ako alokacija ne uspije nmvz, jer u mainu postavljamo trougao da je nullptr i 
    // svakako je brisemo
    //ono na sto pokazuje prvi pokazivac predstavlja cio dinam aloc niz
    try {
        niz_pokazivaca_na_nizove[0] = new int[n*n];
        niz_pokazivaca_na_nizove[0][0] = 1;
        for(int i=1; i<n; i++) {
            niz_pokazivaca_na_nizove[i] = niz_pokazivaca_na_nizove[i-1] + i*2 - 1;
            int broj{i+1};
            for(int j=0; j<=i; j++) {
                niz_pokazivaca_na_nizove[i][j] = broj--;
            }
            broj++;
            for(int j=i; j<2*i+1; j++) {
                niz_pokazivaca_na_nizove[i][j] = broj++;
            }
        }
    }catch(std::bad_alloc) {
        delete[] niz_pokazivaca_na_nizove[0];
        delete[] niz_pokazivaca_na_nizove;
        throw;
    }
    return niz_pokazivaca_na_nizove;
}

int main () {
    std::cout << "Koliko zelite redova: ";
    int n;
    std::cin >> n;
    int **trougao = nullptr;
    try {
        trougao = KreirajTrougao(n);
        for(int i=0; i<n; i++) {
            for(int j=0; j<i*2+1; j++) {
                std::cout << trougao[i][j] << " ";
            }
            std::cout << std::endl;
        }
        delete[] trougao[0];
        delete[] trougao;
    }
    catch(std::domain_error e) {
        std::cout << "Izuzetak: Broj redova mora biti pozitivan" << std::endl;
    }
    catch(std::bad_alloc&) {
        delete[] trougao;
        std::cout << "Izuzetak: Nedovoljno memorije!" << std::endl;
    }
	return 0;
}