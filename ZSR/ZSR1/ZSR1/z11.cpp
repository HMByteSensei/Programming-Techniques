#include <iostream>
#include <cmath>

int main() {
    std::cout << "Unesite vrijednost broja x: ";
    int x = 2;
    //std::cin >> x;
    const double e = 2.718281828;
    double eNAx = 1;
    for(int i=0; i<x; i++)
    {
        eNAx = e * eNAx;
    }
    double S = 1; //x^0 / 0! = 1 i to je prvi clan sume
    int p = 1; //nazivnik
    const double epsilon = 0.00001;
    for(int i=1; i<=100; i++)
    {
        //S= sum(i=1, n) x^i / i!
        if(i==1) continue; //drugi clan sume je x^1/1 = x pa ga ne trba mnoziti sa icim (tj s x)
        else {
            p *= i;
            x = x * x / p;
        }
        S += x;
        if(std::abs(eNAx - S) < epsilon)
        {
            std::cout << "Trazena vrijednost n je: " << i << ". Vrijednost funkcije F je: " << eNAx
            << ", dok je vrijednost funkcije S: " << S << "." << std::endl;
            break;
        }
    }
    return 0;
}