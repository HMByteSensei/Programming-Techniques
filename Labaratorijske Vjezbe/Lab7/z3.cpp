#include <cctype>
#include <iostream>
#include <cmath>
#include <cstring>
#include <new>
#include <algorithm>
#include <string>

int main () {
    std::cout << "Koliko zelite recenica: ";
    int broj;
    std::cin >> broj;
    std::cin.ignore(1000, '\n');
    std::string **recenica = nullptr;
    int brojac{};
    try {
        std::cout << "Unesite recenice:";
        recenica = new std::string*[broj]{};
        for(int i=0; i<broj; i++) {
            recenica[i] = new std::string{};
            // *recenica[i] = recenica[i][0] 
            std::getline(std::cin, recenica[i][0]);
            brojac++;
        }
        std::sort(recenica, (recenica + broj), [] (const std::string *p1, const std::string *p2) {
            return *p1 < *p2;
        });
        //std::sort(recenica, recenica+broj, [](char *p1, char *p2){ return std::strcmp(p1, p2) < 0;});
        
        std::cout << "\nSortirane recenice:\n";
        for(int i=0; i<broj; i++) {
            std::cout << *recenica[i] << std::endl;
        }
    }
    catch(std::bad_alloc) {
        std::cout << "\nProblemi s memorijom!";
    }
    for(int i=0; i<brojac; i++) {
        delete recenica[i];
    }
    delete[] recenica;
	return 0;
}