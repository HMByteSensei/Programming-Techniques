//Autor: Husić Muhamed
#include <iostream>
#include <cmath>
#include <string>
#include <cctype>
#include <vector>

// void PretvoriUVelika(std::string &recenica, std::vector<std::string> &blacklist) {
// }

// nije nas briga kako ce izgledati vektor sa zabranjenim rijeima nakon zavrsetka programa
std::string Cenzura(std::string recenica, std::vector<std::string> blacklist) {
    std::string kopija = recenica;
    //PretvoriUVelika(recenica, blacklist);
    for(int i=0; i<recenica.length(); i++) {
        recenica.at(i) = toupper(recenica.at(i));
    }
    for(int i=0; i<blacklist.size(); i++) {
        for(int j=0; j<blacklist.at(i).length(); j++) {
            blacklist.at(i).at(j) = toupper(blacklist.at(i).at(j));
            if( !(blacklist.at(i).at(j) >= 'A' && blacklist.at(i).at(j) <= 'Z' || blacklist.at(i).at(j) >= '0' && blacklist.at(i).at(j) <= '9') )
                throw std::logic_error("Neispravna riječ");
        }
    }
    for(int i=0; i<recenica.length(); i++) {
        int pocetak_rijeci, kraj_rijeci;
        while(i<recenica.length() && (recenica.at(i) == ' ' || recenica.at(i) == '\t')) i++;
        pocetak_rijeci = i;
        while(i<recenica.length() && (recenica.at(i) >= 'A' && recenica.at(i) <= 'Z' || recenica.at(i) >= '0' && recenica.at(i) <= '9')) i++;
        kraj_rijeci = i;
        std::string poredbeni = recenica.substr(pocetak_rijeci, kraj_rijeci-pocetak_rijeci);
        int duzina_podrijeci = kraj_rijeci - pocetak_rijeci;
        for(int j=0; j<blacklist.size(); j++) {
            if(blacklist.at(j).length() == duzina_podrijeci) {
                if(blacklist.at(j) == poredbeni) {
                    // sa for petljom
                    for(int m=pocetak_rijeci; m<kraj_rijeci; m++) {
                        recenica.at(m) = '*';
                    }
                    // bez for petlje
                    // recenica.erase(pocetak_rijeci, duzina_podrijeci);
                    // recenica.insert(pocetak_rijeci, std::string(duzina_podrijeci, '*'));
                    break;
                }
            }
        }
    }
    std::string rezultat;
    for(int i=0; i<recenica.length(); i++) {
        if(recenica.at(i) == '*') {
            rezultat.push_back('*');
            continue;
        }
        rezultat.push_back(kopija.at(i));
    }
    return rezultat; // recenica je rezultat za sada i treba je vratiti
}

int main () {
    std::cout << "Unesite recenicu: ";
    std::string recenica;
    std::getline(std::cin, recenica);

    std::cout << "Unesite zabranjene rijeci (. za kraj): ";
    std::vector<std::string> zabranjeno;
    std::string element;
    while(std::cin >> element, element != ".") {
        zabranjeno.push_back(element);
    }
    try {
        recenica = Cenzura(recenica, zabranjeno);
        std::cout << "Cenzurisana recenica: " << recenica << std::endl;
    } catch(std::logic_error e) {
        std::cout << "GRESKA: " << "Nelegalne zabranjene rijeci!" << std::endl;
    }

	return 0;
}
