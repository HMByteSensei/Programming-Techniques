#include <iostream>
#include <cmath>
#include <set>
#include <algorithm>

template <typename T>
//auto Unija(std::set<T> skup1, std::set<T> skup2) -> std::set<std::remove_reference_t<decltype(*skup1.begin())>> {
std::set<T> Unija(std::set<T> skup1, std::set<T> skup2) {
    std::set<T> unija;
    for(T x : skup1) unija.insert(x);
    for(T x : skup2) unija.insert(x);
    return unija;
}

template <typename T>
//auto Presjek(std::set<T> skup1, std::set<T> skup2) -> std::set<std::remove_reference_t<decltype(*skup1.begin())>> {
std::set<T> Presjek(std::set<T> skup1, std::set<T> skup2) {
    std::set<T> presjek;
    for(T x : skup1) {
        if(x == *std::find(skup2.begin(), skup2.end(), x)) {
            presjek.insert(x);
        }
    }
    return presjek;
}
int main ()
{
    std::set<int> s1{7,8,9};
    std::set<int> s2{10,9,8};
    std::cout << "Unija: ";
    for(auto x : Unija(s1, s2)) std::cout << x << " ";
    std::cout << std::endl << "Presjek: ";
    for(auto x : Presjek(s1, s2)) std::cout << x << " ";
	return 0;
}
