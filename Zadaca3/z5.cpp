//TP 2022/2023: Zadaća 3, Zadatak 3
#include <iostream>
#include <cmath>
#include <set>

struct Cvor {
    int redni_broj;
    Cvor *sljedeci;
};


int Poglavica(int N_punoljetnih, int korak_M, bool ispis = false) {
    if(N_punoljetnih <= 0 || korak_M <= 0) return 0;
    Cvor *pocetni=nullptr, *predhodni = nullptr;
    for(int i=1; i <= N_punoljetnih; i++) {
        Cvor *novi = new Cvor{i, nullptr};
        if(i == 1) pocetni = novi;
        else predhodni->sljedeci = novi;
        predhodni = novi;
    }
    predhodni->sljedeci = pocetni;
    int brojac{1};
    auto it_prije = predhodni;
    //std::cout << "\nPOCETAK\n";
    for(auto it = pocetni; it != it_prije;) 
    {
        //std::cout << "\nit = " << it->redni_broj << "  it_prije = " << it_prije->redni_broj << "  brojac = " << brojac;
        if(brojac == korak_M) {
            //std::cout << "\nISPIS: ";
            if(ispis) std::cout << it->redni_broj << ", ";
            auto pomocni = it->sljedeci;
            if(korak_M != 1) it_prije->sljedeci = pomocni;
            delete it;
            it = pomocni;
            brojac = 1;
        }
        if(korak_M != 1) it = it->sljedeci, it_prije = it_prije->sljedeci, brojac++;
    }
    if(ispis) std::cout << "\n";
    int rez = it_prije->redni_broj;
    delete it_prije;
    return rez;
}

int SigurnoMjesto(int korak_M, int N1, int N2) {
    if(korak_M <= 0 || N1 <= 0) return 0;
    if(N1 > N2) return 0;
    std::set<int> skup;
    for(int N = N1; N<=N2; N++) skup.insert(N);
    for(; N1 <= N2; N1++) { 
        skup.erase(Poglavica(N1, korak_M));
    }
    if(skup.empty()) return 0;
    return *skup.begin();
}

int main ()
{
    // main iz zadatka 4
    std::cout << "Unesite broj punoljetnih clanova za odabir poglavice plemena Wabambe: ";
    int broj_osoba;
    std::cin >> broj_osoba;
    std::cin.ignore(1000, '\n');
    std::cout << "Unesite korak razbrajanja: ";
    int korak;
    std::cin >> korak;
    std::cin.ignore(1000, '\n');
    std::cout << "Unesite raspon za odabir (N1 i N2): ";
    int N1, N2;
    std::cin >> N1 >> N2;
    //std::cout << "\nbroj_osoba = " << broj_osoba << "    korak = " << korak << " n1 = " << N1 << " n2 " << N2;
    std::cout << "Redni broj osobe koja postaje poglavica: " << Poglavica(broj_osoba, korak);
    int mjesto = SigurnoMjesto(korak, N1, N2);
    if(mjesto) std::cout << "\nMbebe Mgogo, stani na sigurno mjesto " << mjesto << " da ne bi bio poglavica!";
    else std::cout << "\nZao mi je Mbebe Mgogo, ali nema sigurnog mjesta.";
	return 0;
}