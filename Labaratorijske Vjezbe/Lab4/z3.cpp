#include <iostream>
#include <cmath>
#include <vector>
#include <cctype>

void IzdvojiKrajnjeRijeci(const std::vector<std::string> &vektor_rijeci, std::string &prva, std::string &zadnja) {
    std::vector<std::string> kopija{vektor_rijeci};
    for(std::string &s : kopija) {
        for(int i=0; i<s.length(); i++) {
            s.at(i) = toupper(s.at(i));
        }
    }
    if(vektor_rijeci.size() == 0) {
        prva = "";
        zadnja = "";
        return;
    }
    prva = kopija.at(0);
    zadnja = kopija.at(0);
    int index_min{0}, index_max{0};
    // vektor_rijeci i kopija su iste duzine pa moze i kopija.size()
    for(int i=0; i<vektor_rijeci.size(); i++) {
        if(prva > kopija.at(i)) {
            prva = kopija.at(i);
            index_min = i;
        }
        if(zadnja < kopija.at(i)) {
            zadnja = kopija.at(i);
            index_max = i;
        }
    }
    prva = vektor_rijeci.at(index_min);
    zadnja = vektor_rijeci.at(index_max);
}

void ZadrziDuplikate(std::vector<std::string> &vektor_rijeci) {
    for(int i=0; i<vektor_rijeci.size(); i++) {
        // da li ima duplikata
        bool duplikata{false};
        for(int j=i+1; j<vektor_rijeci.size(); j++ ) {
            if(vektor_rijeci.at(i) == vektor_rijeci.at(j)) {
                duplikata = true;
                break;
            }
        }
        // ako nema duplikata
        if(!duplikata) {
            for(int j=i; j<vektor_rijeci.size()-1; j++) {
                vektor_rijeci.at(j) = vektor_rijeci.at(j+1);
            }
            i--;
            vektor_rijeci.resize(vektor_rijeci.size()-1);
        } // ako ima duplikata
        else {
            for(int j=i+1; j<vektor_rijeci.size()-1; j++) {
                if(vektor_rijeci.at(i) == vektor_rijeci.at(j)) {
                    for(int k=j; k<vektor_rijeci.size()-1; k++) {
                        vektor_rijeci.at(k) = vektor_rijeci.at(k+1);
                    }
                    j--;
                    vektor_rijeci.resize(vektor_rijeci.size()-1);
                }
            }
        }
    }
}

int main ()
{
    std::cout << "Koliko zelite unijeti rijeci: ";
    int broj_rijeci;
    std::cin >> broj_rijeci;
    std::cout << "Unesite rijeci: ";
    std::vector<std::string> v;
    for(int i=0; i<broj_rijeci; i++) {
        std::string element;
        std::cin >> element;
        v.push_back(element);
    }
    std::string prva, posljednja;
    IzdvojiKrajnjeRijeci(v, prva, posljednja);
    std::cout << "Prva rijec po abecednom poretku je: " << prva << std::endl;
    std::cout << "Posljednja rijec po abecednom poretku je: " << posljednja << std::endl;
    std::cout << "Rijeci koje se ponavljaju su:";
    ZadrziDuplikate(v);
    // Autor: Muhamed Husic
    for(std::string &x : v) {
        std::cout << " " << x;
    }
	return 0;
}
