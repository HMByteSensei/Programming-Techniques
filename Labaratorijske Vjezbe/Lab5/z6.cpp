#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

int main ()
{
    std::cout << "Unesite broj elemenata: ";
    int n;
    std::cin >> n;
    std::cout << "Unesite elemente: ";
    std::vector<int> vektor(n);
    for(int i=0; i<n; i++) {
        int element;
        std::cin >> element;
        vektor.at(i) = element;
    }
    bool (*p)(int, int) = [](int x, int y) -> bool {
        int suma_x{0}, suma_y{0};
        int kopija_x = std::fabs(x), kopija_y = std::fabs(y); 
        while(kopija_x != 0) {
            int ostatak = kopija_x % 10;
            suma_x += ostatak;
            kopija_x /= 10;
        }
        while(kopija_y != 0) {
            int ostatak = kopija_y % 10;
            suma_y += ostatak;
            kopija_y /= 10;
        }
        if(suma_y == suma_x) {
            return x < y;
        }
        return suma_x < suma_y;
    };
    std::sort(vektor.begin(), vektor.end(), p);
    std::cout << "Niz sortiran po sumi cifara glasi: ";
    std::for_each(std::begin(vektor), std::end(vektor), [](int x){std::cout << x << " ";});
    std::cout << std::endl << "Unesite broj koji trazite: ";
    int trazeni_broj;
    std::cin >> trazeni_broj;
    int index_trazenog_broja = std::lower_bound(vektor.begin(),vektor.end(),trazeni_broj,p) - vektor.begin();
    // da ne bi izasli van opsega ako imamo npr.: 1,2,3,4,5 i trazimo br veci od 5
	if(index_trazenog_broja < vektor.size() && trazeni_broj == vektor.at(index_trazenog_broja))
        std::cout << "Trazeni broj nalazi se na poziciji " << index_trazenog_broja << std::endl;
    else std::cout << "Trazeni broj ne nalazi se u nizu!" << std::endl; 
    return 0;
}