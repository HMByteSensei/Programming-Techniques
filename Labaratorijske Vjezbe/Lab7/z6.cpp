#include <iostream>
#include <cmath>
#include <list>
#include <iterator>

template <typename ManjiOD>
// auto SortirajListu(std::list<ManjiOD> &lista) -> std::list<std::remove_reference_t<decltype(*lista.begin())>> {
void SortirajListu(std::list<ManjiOD> &lista) {
    std::list<ManjiOD> sortirana;
    //std::cout << "\nU fiji\n";
    typename std::list<ManjiOD>::iterator p = lista.begin();
    while(p != lista.end()){
        //std::cout << "\nU petlni\n";
        typename std::list<ManjiOD>::iterator nova = sortirana.begin();
        while(nova != sortirana.end() && *p > *nova) {
            nova++;
        }
        //nova--;
        sortirana.insert(nova, *p);
        p++;
    }
    lista = sortirana;
}

int main () {
    std::cout << "Koliko ima elemenata: ";
    int br;
    std::cin >> br;
    //std::cin.ignore(1000, '\n');
    std::cout << "Unesite elemente: ";
    std::list<int> l;
    for(int i=0; i<br; i++) {
        int x;
        std::cin >> x;
        //std::cin.ignore(1000, '\n');
        l.push_back(x);
    }
    std::cout << "Sortirana lista: ";
    SortirajListu(l);
    for(auto x : l) {
        std::cout << x << " ";
    }
	return 0;
}
