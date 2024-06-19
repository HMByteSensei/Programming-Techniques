#include <iostream>
#include <cmath>
#include <vector>

template <typename IterTip>
auto SumaBloka(IterTip p1, IterTip p2) -> decltype(*p1 + *p1) {
    // zasto ne radi p1+1 == p2 kada p2 pokazuje iza kraja niza
    // pa ako imamo 0 elemenata p1 pokazuje na nulti, a p2 na prvi i bilo bi logicno da p1+1 = p2 u tom 
    // slucaju ali nije tako?
    if( p1 == p2 ) {
        throw std::range_error("Blok je prazan");
    }
    decltype(*p1 + *p1) suma{};
    while(p1 != p2) {
        // prvo dereferencira pok (*p1) a onda povecava adresu pokazivaca (p1++)
        suma += *p1++;
    }
    return suma;
}

int main ()
{
    //AT2: testiramo funkciju SumaBloka za vektor cijelih brojeva

    std::vector<double> v{-95,25,333,96,6,12,1,2,35,0};
    std::cout<<"Suma bloka je: "<<SumaBloka(v.begin(), v.end());

	return 0;
}