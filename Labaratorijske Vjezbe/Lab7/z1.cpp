#include <cctype>
#include <iostream>
#include <cmath>
#include <cstring>
#include <new>

int main ()
{
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
        for(int i=0; i<broj; i++) {
            bool stani{false};
            for(int j=i+1; j < broj; j++) {
                if(stani) break;
                for(int k=0; recenica[i][k] != '\0'; k++) {
                    if(std::toupper(recenica[i][k]) > std::toupper(recenica[j][k]) || recenica[j][k] == '\0') {
                        //recenica[j] je manja pa dolazi ispred
                        char *pomocna = recenica[i];
                        recenica[i] = recenica[j];
                        recenica[j] = pomocna;
                        if(i != 0) {
                            stani = true;
                            i--;
                        }
                        break;
                    }
                    else if(std::toupper(recenica[i][k]) < std::toupper(recenica[j][k])) {
                        break;
                    }
                }
            }
        }
        
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