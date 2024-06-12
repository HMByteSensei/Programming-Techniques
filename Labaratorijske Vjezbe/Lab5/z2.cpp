#include <iostream>
#include <utility>
#include <type_traits>
#include <vector>
#include <deque>

template <typename IterTip1, typename IterTip2>
//typename std::common_type<IterTip1, IterTip2>::type 
IterTip2 RazmijeniBlokove(IterTip1 p1, IterTip1 p2, IterTip2 p3) {
    while(p1 != p2) {
        // std::swap(*p1, *p3);
        auto pomocna = *p1;
        *p1 = *p3;
        *p3 = pomocna;
        p1++;
        p3++;
    }
    return p3;
}

int main () {
    int niz[]{1,2,3,4,5,6,7};
    int niz2[]{8,9,10,11,12,13,14};
    RazmijeniBlokove(std::begin(niz), std::end(niz), std::begin(niz2));
    std::cout << "Prvi niz: ";
    // Autor: Muhamed Husic
    for(int x : niz) std::cout << x << " ";
    std::cout << "\nDrugi niz: ";
    for(int x : niz2) std::cout << x << " ";
    std::cout << std::endl;
    std::string s{"Ovo je neka rijec u recenici."};//29
    std::string s2{"Sada treba razmijeniti ove rijeci."};
    RazmijeniBlokove(s.begin(), s.end(), s2.begin());
    std::cout << "Prvi kontejner: ";
    for(char x : s) std::cout << x;
    std::cout << "\nDrugi kontejner: ";
    for(char x : s2) std::cout << x;
    std::cout << std::endl;
	return 0;
}