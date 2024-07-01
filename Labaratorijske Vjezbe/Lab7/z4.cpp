#include <cctype>
#include <iostream>
#include <cmath>
#include <cstring>
#include <memory>
#include <algorithm>
#include <string>


int main () {
    std::cout << "Koliko zelite recenica: ";
    int broj;
    std::cin >> broj;
    std::cin.ignore(1000, '\n');
    //std::unique_ptr<std::shared_ptr<std::string>> *recenica = new std::unique_ptr<std::shared_ptr<std::string>>[broj];
    
    

    
    // ne radi
    //std::shared_ptr<std::unique_ptr<std::string>> recenica = std::make_shared<std::make_unique<std::string>>[broj];

    int brojac{};
    try {
        std::cout << "Unesite recenice:";
        std::unique_ptr<std::shared_ptr<std::string>[]>recenica (new std::shared_ptr<std::string>[broj]); //ovdje ne moze znak =
        for(int i=0; i<broj; i++) {
            //recenica[i] (new std::unique_ptr<std::string>{});
            recenica[i] = std::make_shared<std::string>();
            std::getline(std::cin, *recenica[i]);
            brojac++;
        }
        std::sort(recenica.get(), (recenica.get() + broj), [] (const std::shared_ptr<std::string> &p1, const std::shared_ptr<std::string> &p2) {
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
	return 0;
}