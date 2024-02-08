//TP 2022/2023: Zadaća 3, Zadatak 3
// radio sam 4 greskom u fajlu za 3 pa sam ovdje kopiro
#include <iostream>
#include <cmath>
#include <list>
#include <iterator>
#include <set>

int Poglavica(int N_punoljetnih, int korak_M, bool ispis = false) {
    std::list<int> broj_osoba;
    if(N_punoljetnih <= 0 || korak_M <= 0) return 0; // nema smisla da broj osoba niti korak budu <= 0
    for(int i=1; i<=N_punoljetnih; i++) {
        broj_osoba.push_back(i);
    }
    int brojac{1};
    for(auto it = broj_osoba.begin();;) {
        // ako imamo samo jednu osobu onda smo pronasli poglavara
        if(broj_osoba.size() == 1) {
            break;
        }
        if(broj_osoba.size() > 1 && it == broj_osoba.end()) {
            // liste nisu kruzne(tj nije tako propisano standardom), pa se rucno vracam
            it = broj_osoba.begin();
        }
        for(; it != broj_osoba.end(); it++, brojac++) 
        {
            //std::cout << "\nU petlji brojac: " << brojac << "\t korakM = " << korak_M << " *it = " << *it;
            if(brojac == korak_M) {
                //std::cout << "\n\t U if klauzi!";
                if(ispis) std::cout << *it << ", ";
                it = broj_osoba.erase(it);
                brojac = 1; // jer smo vec preuzeli iterator na sljedeci
                if(korak_M == 1) it--; // u sljedecoj iteraciji povecavam ovo dvoje, pa ako je korak 1, a nema ovog uslova onda preskacem jedan element
                if(it == broj_osoba.end()) break; // ako nema ovog onda odemo na prvi element, pa se samo nastavi, tj cini mi se da je ovdje lista implementirana kao ciklicna
            }
            //break;
        }
        //if(*it == 4) break;
    }
    if(ispis) std::cout << "\n";
    return *broj_osoba.begin();
}

int SigurnoMjesto(int korak_M, int N1, int N2) {
    if(korak_M <= 0 || N1 <=0) return 0;
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