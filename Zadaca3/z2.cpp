//TP 2022/2023: Zadaća 3, Zadatak 2
#include <iostream>
#include <cmath>
#include <map>
#include <stdexcept>
#include <vector>
#include <string>
#include <tuple>
#include <set>
#include <cctype> // za isalpha
#include <algorithm>

typedef std::map<std::string, std::vector<std::string>> Knjiga;
typedef std::tuple<std::string, int, int> TIP;

// std::set ima implementiran izgleda sort za tuple pa nema potrebe da ga mi implementiramo
std::map<std::string, std::set<std::tuple<std::string, int, int>>> KreirajIndeksPojmova(const Knjiga &analizirani_text) {
    std::map<std::string, std::set<TIP>> rjecnik;
    // po poglavljima petlja
    for(auto it_pog = analizirani_text.begin(); it_pog != analizirani_text.end(); it_pog++) {
        // jedan element(string) u vektoru = jedna stranica
        for(auto it_str = it_pog->second.begin(); it_str != it_pog->second.end(); it_str++) {
            std::string rijec{};
            // po stringovima unutar vektora tj. po rijecima u recenica
            for(auto it = (*it_str).begin(); it != it_str->end(); it++) {
                const auto pozicija = it + 1; // jer indeksacija pocinje od 0 a nama treba od 1, a nebitno je na sta tacno pozicija pokazuje, pa je const da je ne bi slucajno dirali
                while( it != it_str->end() && ( std::isalpha(*it) || (*it >= '0' && *it <= '9') ) ) 
                {
                    rijec.push_back(std::tolower(*it));
                    it++;
                }
                if(!rijec.empty()) 
                {
                    TIP uredena_trojka = TIP(it_pog->first, (it_str - it_pog->second.begin() + 1), pozicija - it_str->begin() - 1);
                    rjecnik[rijec].insert(uredena_trojka);
                    rijec = ""; // vracamo rijec na prazan string
                }
                if(it == it_str->end()) break; // iz nekog razloga nece da radi bez ove linije iako for loop sadrzi ovaj uslov
            }
        }
    }

    return rjecnik;
}

// ako stavim const &index_pojmova onda moram koristiti at koji je sporiji pa je samo ref
std::set<TIP> PretraziIndeksPojmova(std::string trazena_rijec, std::map<std::string, std::set<TIP>> &index_pojmova) {
    if(index_pojmova.find(trazena_rijec) != index_pojmova.end()) {
        return index_pojmova[trazena_rijec];
    }
    throw std::logic_error("Pojam nije nadjen");
}

void IspisiIndeksPojmova(const std::map<std::string, std::set<TIP>> &index_pojmova) {
    for(auto it = index_pojmova.begin(); it != index_pojmova.end(); it++) {
        std::cout << it->first << ": ";
        for(auto set_it = it->second.begin(); set_it != it->second.end(); set_it++) {
            std::cout << std::get<0>(*set_it) << "/" << std::get<1>(*set_it) << "/" << std::get<2>(*set_it);
            if(std::next(set_it) != it->second.end()) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }
}

// Autor: Muhamed Husić
int main ()
{
    Knjiga knjiga;
    for(;;) {
        std::cout << "\nUnesite naziv poglavlja: ";
        std::string naziv_poglavlja;
        std::getline(std::cin, naziv_poglavlja);
        if(naziv_poglavlja == ".") break;
        std::vector<std::string> stranica_poglavlja;
        for(int i=1; ; i++) {
            std::cout << "\nUnesite sadrzaj stranice " << i << ": ";
            std::string stranica;
            std::getline(std::cin, stranica);
            if(stranica == ".") break;
            stranica_poglavlja.push_back(stranica);
        }
        knjiga[naziv_poglavlja] = stranica_poglavlja;
    }

    // Ispisivanje svih indeksa pojmova koje smo uspjeli pronaci
    std::cout << "\nKreirani indeks pojmova:\n";
    std::map<std::string, std::set<TIP>> indexpojmova;
    indexpojmova = KreirajIndeksPojmova(knjiga);
    IspisiIndeksPojmova(indexpojmova);

    for(;;) {
        std::cout << "Unesite rijec: ";
        std::string trazi;
        // rijec koja se trazi mora biti jedna cjelina tj ne mozemo pretrazivati recenica
        if((std::cin >> trazi), trazi == ".") break;
        try {
            std::transform(trazi.begin(), trazi.end(), trazi.begin(), [](char znak) {return std::tolower(znak);}); // sa predavanja 5 b
            std::set<TIP> pretrazi = PretraziIndeksPojmova(trazi, indexpojmova);
            std::cout << std::endl;
            for(auto x = pretrazi.begin(); x != pretrazi.end(); x++) {
                std::cout << std::get<0>(*x) << "/" << std::get<1>(*x) << "/" << std::get<2>(*x);
                std::cout << " ";
                // ispisivanje zareza za sve elemente osim zadnjeg
                // if(std::next(x) != pretrazi.end()) {
                //     std::cout << ", ";
                // }
            }
            std::cout << std::endl;
        } catch(std::logic_error e) {
            std::cout << "\nUnesena rijec nije nadjena!\n";
        }
    }

	return 0;
}