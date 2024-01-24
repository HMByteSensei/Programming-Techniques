//TP 2022/2023: Zadaća 2, Zadatak 2
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <limits.h>

// za n=0 i n=1
void RastavaBroja(int n, int &p, int &q) {
    // 𝑛 = 0, pri čemu tada treba uzeti 𝑝 = 0 i  q = 1 -> pise u zadatku pa nije hard kodiranje
    if(n == 0) {
        p=0;
        q=1;
        return;
    }

    // vektor u kojem cemo smjestiti faktore
    std::vector<int> faktori;

    // ako je n negativan broj
    bool negativan{false};
    if(n<0) {
        negativan = true;
        n = (-n);
    }
    int kopija = n;
    // da ga ne racunam vise puta
    int korijen = std::sqrt(n);
    //int brojac = 0;
    
    // malo brze je ovako
    while(n % 2 == 0) {
        faktori.push_back(2);
        n /= 2;
    }
    // svaki slozeni broj se sastoji od prostih, pa ne moramo spec provjervati da li je broj prost ili ne
    for(int i=3; i <= korijen; i+=2) {
        while(n % i == 0) {
            faktori.push_back(i);
            // update broj n
            n /= i;
        }
    }

    // da li je ostatak prost
    if(n > 2) {
        faktori.push_back(n);
    }
    // postaviti vrijednosti p na jedan(neutralan element za mnozenje) jer cemo odmah na njega dodavati 
    // elemente
    p = 1;
    for(int i=0; i<faktori.size(); i++) {
        //int brojac = std::count(faktori.begin() + i, faktori.end(), faktori.at(i));

        //brze mozda
        int faktor = faktori.at(i);
        int brojac = 1;
        //std::cout << "Element: " << faktori.at(i) << "\tpojavljuje: " << brojac<<"\n";
        while(i+1 < faktori.size() && faktori.at(i+1) == faktor) {
            brojac++;
            i++;
        }
        if((brojac % 2) != 0) {
            p *= faktori.at(i);            
        }
        //i += brojac;
    }
    q = std::sqrt(kopija / p);
    if(negativan) p = (-p);
    //std::cout << "\nn = " << kopija << "\tp = " << p << "\tq = " << q << "\n";
}

int main ()
{
    std::cout << "Unesi broj: ";
    int broj;
    std::cin >> broj;
    int a, b;
    RastavaBroja(broj, a, b);
    std::cout << std::endl << broj << " = " << a << "*" << b << "^2" << std::endl;
   
    return 0;
}
