//TP 2022/2023: LV 4, Zadatak 1
#include <iostream>
#include <cmath>
#include <limits>

int Cifre(long long n, int &c_min, int &c_max) {
    unsigned long long int poz = (n<0 ? -n : n);
    if(n==0) { 
        c_min = 0;
        c_max = 0;
        return 1;
    }
    c_min = poz%10;
    c_max = poz%10;
    int broj_cifri = log10(poz) + 1;
    for(int i=0; i<broj_cifri; i++) {
        int ostatak = poz % 10;
        poz /= 10;
        if(ostatak < c_min) {
            c_min = ostatak;
        }
        if(ostatak > c_max) {
            c_max = ostatak;
        }
    }
    return broj_cifri;
}
// Autor: Muhamed Husić
int main ()
{
    std::cout << "Unesite broj: ";
    long long int broj;
    std::cin >> broj;
    int min, max;
    std::cout << "Broj " << broj << " ima " << Cifre(broj, min, max) << " cifara, najveca je " << max << " a najmanja " << min << "." << std::endl;
	return 0;
}
