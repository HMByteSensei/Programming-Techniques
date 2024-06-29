#include <cctype>
#include <iostream>
#include <cmath>
#include <cstring>
#include <new>
#include <algorithm>

int main () {
    std::cout << "Koliko zelite recenica: ";
    int broj;
    std::cin >> broj;
    std::cin.ignore(1000, '\n');
    char **recenica = nullptr;
    int brojac = 0;
    try {
        std::cout << "Unesite recenice:";
        recenica = new char*[broj];
        for(int i=0; i<broj; i++) {
            char jedna[1000];
            std::cin.getline(jedna, sizeof jedna);
            recenica[i] = new char[std::strlen(jedna) + 1];
            std::strcpy(recenica[i], jedna);
            brojac++;
        }
        std::sort(recenica, (recenica + broj), [](char *p1, char *p2) {
            int i=0;
            while(p1[i] != '\0') {
                if(p2[i] == '\0' || p2[i] < p1[i]) {
                    // Autor: Muhamed Husić
                    return false;
                }
                else if(p2[i] > p1[i]) {
                    return true;
                }
                i++;
            }
            return true;
        });
        //std::sort(recenica, recenica+broj, [](char *p1, char *p2){ return std::strcmp(p1, p2) < 0;});
        
        std::cout << "\nSortirane recenice:\n";
        for(int i=0; i<broj; i++) {
            std::cout << recenica[i] << std::endl;
        }
        for(int i=0; i<broj; i++) {
            delete[] recenica[i];
        }
        delete[] recenica;
    }
    catch(std::bad_alloc) {
        std::cout << "\nProblemi s memorijom!";
        for(int i=0; i<brojac; i++) {
            delete[] recenica[i];
        }
        delete[] recenica;
    }
	return 0;
}