#include <iostream>
#include <cmath>
#include <map>
#include <string>
#include <algorithm>
#include <iterator>

std::string ZamijeniPremaRjecniku(const std::string &recenica, std::map<std::string, std::string> &rijecnik) {
    std::string rezultat = recenica;
    auto p = rezultat.begin();
    while(p != rezultat.end()) {
        while(p != rezultat.end() && (*p == ' ' || *p == '\t')) p++;
        auto kopija = p;
        while(p != rezultat.end() && (*p != ' ' && *p != '\t')) p++;
        std::string pomocna(kopija, p);
        //std::cout << "\nPomocna: " << pomocna;
        if(rijecnik.count(pomocna)) {
            int pozicija = kopija - rezultat.begin(), znakova = p - kopija;
            rezultat.replace(pozicija, znakova, rijecnik[pomocna]);
            //rezultat.insert(pozicija, rijecnik[pomocna]);
            p = rezultat.begin() + pozicija + rijecnik[pomocna].length();
        }
    }
    std::cout << "\n";
    return rezultat;
}

int main ()
{
    // std::map<std::string, std::string> rijecnik{{"nije", "not"}, {"kako", "how"}, {"nesto", "something"}, {"kul", "cool"}};
    // std::string s = "Kako nije kul nesto";
    // std::string a = ZamijeniPremaRjecniku(s, rijecnik);
	// std::cout <<"\n"<< a;
    std::map<std::string, std::string> rjecnik 
    { 
        {"jabuka", "apple"}, 
        {"da", "yes"}, 
        {"kako", "how"}, 
        {"ne", "no"}, 
        {"majmun", "monkey"}, 
        {"mart", "ozujak"},
        {"maj", "svibanj"}, 
        {"jul", "srpanj"}
    };
    
  std::cout << ZamijeniPremaRjecniku("danas je 8. mart a 1. maj je praznik rada", rjecnik) << std::endl;
    return 0;
}