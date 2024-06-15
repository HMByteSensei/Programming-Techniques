#include <iostream>
#include <algorithm>
#include <cmath>

void unesi(int broj, int (&niz)[1000], int &i)
{
    //static int i=0;
    if(i < broj)
    {
        std::cin >> niz[i];
        i++;
        unesi(broj, niz, i);
    }
}

void asd(int &x) {
        std::cin >> x;
}

bool wqe(int x) {
        return (std::sqrt(x) == static_cast<int>(std::sqrt(x)));
    }

bool poredi(int x, int y)  {
        int cifara_x = log10(std::fabs(x)) + 1;
        int cifara_y = log10(std::fabs(y)) + 1;
        return cifara_x < cifara_y;
    }

void mm(int x) {
        if((static_cast<int>(log10(std::fabs(x)) + 1)) != 3)
            std::cout << x << " ";
        return;
    }
int main () {
    int niz[1000];
    std::cout << "Unesite broj elemenata (max. 1000): ";
    int n, a=0;
    std::cin >> n;
    unesi(n, niz, a);
    std::cout << "Unesite elemente: ";
    // Autor: Muhamed Husić
    std::for_each(std::begin(niz), std::begin(niz) + n, asd);
    std::cout << "Najveci element niza je " << *std::max_element(std::begin(niz), std::begin(niz) + n) << std::endl;
    std::cout << "Najmanji element niza se pojavljuje " 
    << std::count(std::begin(niz), std::begin(niz)+n, *std::min_element(std::begin(niz), std::begin(niz) + n)) << " puta u nizu" << std::endl;
       
    std::cout << "U nizu ima " << std::count_if(std::begin(niz), std::begin(niz)+n, wqe) << " brojeva koji su potpuni kvadrati" << std::endl;

    std::cout << "Prvi element sa najmanjim brojem cifara je " <<
    *std::min_element(std::begin(niz), std::begin(niz)+n, poredi) << std::endl;
    std::cout << "Elementi koji nisu trocifreni su: ";
    std::for_each(std::begin(niz), std::begin(niz) + n, mm);

	return 0;
}