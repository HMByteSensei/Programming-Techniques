#include <iostream>
#include <algorithm>
#include <cmath>
#include <deque>



int main () {
    std::cout << "Unesite broj elemenata: ";
    int n;
    std::cin >> n;
    std::deque<int> niz(n);
    int a =0;
   
    std::cout << "Unesite elemente: ";

    std::for_each(niz.begin(), std::begin(niz)+n, [](int &x) {
        std::cin >> x;
    });
    std::cout << "Najveci element deka je " << *std::max_element(std::begin(niz), niz.end()) << std::endl;
    std::cout << "Najmanji element deka se pojavljuje " 
    << std::count(niz.begin(), niz.end(), *std::min_element(std::begin(niz), niz.end())) << " puta u deku" << std::endl;
       
    std::cout << "U deku ima " << std::count_if(std::begin(niz), niz.end(), [](int x) -> bool {
        return (std::sqrt(x) == static_cast<int>(std::sqrt(x)));
    }) << " brojeva koji su potpuni kvadrati" << std::endl;

    std::cout << "Prvi element sa najmanjim brojem cifara je " <<
    *std::min_element(std::begin(niz), niz.end(), [](int x, int y) -> bool {
        int cifara_x = log10(std::fabs(x)) + 1;
        int cifara_y = log10(std::fabs(y)) + 1;
        return cifara_x < cifara_y;
    }) << std::endl;
    std::cout << "Elementi koji nisu trocifreni su: ";
    std::for_each(std::begin(niz), niz.end(), [](int x) {
        if((static_cast<int>(log10(std::fabs(x)) + 1)) != 3)
            std::cout << x << " ";
        return;
    });

	return 0;
}