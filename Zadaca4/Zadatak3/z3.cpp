//TP 2022/2023: Zadaća 4, Zadatak 3
// Autor: Muhamed Husić
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <iomanip>
#include <algorithm>

class Polazak {
    std::string odrediste, oznaka_voznje;
    int broj_perona, sat_polaska, minute_polaska, trajanje_voznje, vrijeme_kasnjenja;
    static int PretvoriUMinute(const int &sat, const int &minute) { return 60 * sat + minute; }
    static std::pair<int, int> PretvoriUSateIMinute(int minute);
public:
    Polazak(std::string odrediste, std::string oznaka_voznje,  int broj_perona,    int sat_polaska, int minute_polaska, int trajanje_voznje); 
    void PostaviKasnjenje(int kasnjenje); 
    bool DaLiKasni() const { return vrijeme_kasnjenja > 0; } 
    int DajTrajanje() const { return trajanje_voznje; }
    void OcekivanoVrijemePolaska(int &sati, int &minute) const; 
    void OcekivanoVrijemeDolaska(int &sati, int &minute) const;
    void Ispisi() const;
};

void Polazak::Ispisi() const {
    static std::string a = "";
    std::cout << a << oznaka_voznje <<std::setw(10) << odrediste << std::setw(5) << ""  
    << std::setfill('0') << std::setw(31) << std::setfill(' ');
    int sat = sat_polaska, min = minute_polaska;
    OcekivanoVrijemeDolaska(sat, min);
    if(!DaLiKasni()) 
    {
        std::cout << sat_polaska << ":" <<  std::setw(2) << std::setfill('0') << minute_polaska;
        std::cout << std::setw(5) << std::setfill(' ') << "" << std::setw(2) << sat << ":" <<  std::setw(2)
        << std::setfill('0') << min << std::setw(8) << std::setfill(' ') << broj_perona;
    } else {
        sat = sat_polaska, min = minute_polaska + vrijeme_kasnjenja;
        PretvoriUMinute(sat, min);
        // da ne pozivam funkciju dva puta
        std::pair<int,int> t = PretvoriUSateIMinute(PretvoriUMinute(sat, min));
        sat = t.first;
        min = t.second;
        std::cout << sat << ":" << std::setfill('0') << std::setw(2)
        << min << std::setw(8) << " (Planirano " << sat_polaska << ":" << std::setfill('0')
        << std::setw(2) << minute_polaska << ", Kasni " << vrijeme_kasnjenja << " min)" << std::setfill(' ') << "";
    }
    a="\n";
}

Polazak::Polazak(std::string odrediste, std::string oznaka_voznje,  int broj_perona,    int sat_polaska, int minute_polaska, int trajanje_voznje) 
    : vrijeme_kasnjenja(0), odrediste(odrediste), oznaka_voznje(oznaka_voznje) {
    if(broj_perona < 1 || broj_perona > 15 || sat_polaska < 0  || sat_polaska > 23 || minute_polaska < 0 || minute_polaska > 60 
       || trajanje_voznje < 1) {
        throw std::domain_error("Pogresan unos, imajte na umu da dozvoljena oznaka za broj perona je od 1 do 15 ukljucivo.");
    }
    Polazak::broj_perona = broj_perona;
    Polazak::sat_polaska = sat_polaska;
    Polazak::minute_polaska = minute_polaska;
    Polazak::trajanje_voznje = trajanje_voznje;
}

void Polazak::PostaviKasnjenje(int kasnjenje) {
    if(kasnjenje < 0) {
        throw std::domain_error("Kasnjenje je izrazeno u minutama za koje nema smisla da budu negativne.");
    }
    vrijeme_kasnjenja = kasnjenje;
}

std::pair<int, int> Polazak::PretvoriUSateIMinute(int minute) {
    std::pair<int, int> h_m{0,0};
    while(minute >= 60) {
        h_m.first += minute / 60;
        minute %= 60;
    }
    h_m.second = minute;
    while(h_m.first > 23) {
        h_m.first = h_m.first % 24;
    }
    return h_m;
}

void Polazak::OcekivanoVrijemePolaska(int &sati, int &minute) const {
    int vrijeme = PretvoriUMinute(sat_polaska, minute_polaska) + vrijeme_kasnjenja;
    // da ne pozivam funkciju dva puta
    std::pair<int,int> kasnjenje = PretvoriUSateIMinute(vrijeme);
    sati = kasnjenje.first;
    minute = kasnjenje.second;
}

void Polazak::OcekivanoVrijemeDolaska(int &sati, int &minute) const{ 
    minute = minute_polaska + trajanje_voznje;
    int vrijeme = PretvoriUMinute(sat_polaska, minute) + vrijeme_kasnjenja;
    std::pair<int,int> kasnjenje = PretvoriUSateIMinute(vrijeme);
    sati = kasnjenje.first;
    minute = kasnjenje.second;
}
//---------------------------------------------------KRAJ KLASE/NOVA KLASA--------------------------------//

class Polasci {
    Polazak **spisak_polazaka{};
    int broj_polazaka;
    //const 
    int max_broj_polazaka;
public:
    explicit Polasci(int max_broj_polazaka) : broj_polazaka(0), max_broj_polazaka(max_broj_polazaka), spisak_polazaka(new Polazak*[max_broj_polazaka]{}) {} 
    Polasci(std::initializer_list<Polazak> lista_polazaka);
    ~Polasci();
    Polasci(const Polasci &polasci);
    Polasci(Polasci &&polasci); 
    Polasci &operator =(const Polasci &polasci); 
    Polasci &operator =(Polasci &&polasci); 
    void RegistrirajPolazak(std::string odrediste, std::string oznaka_voznje, int broj_perona, int sat_polaska, int minute_polaska, int trajanje_voznje); 
    void RegistrirajPolazak(Polazak *polazak); 
    int DajBrojPolazaka() const { return broj_polazaka; }
    int DajBrojPolazakaKojiKasne() const;
    Polazak &DajPrviPolazak(); 
    Polazak DajPrviPolazak() const; 
    Polazak &DajPosljednjiPolazak(); 
    Polazak DajPosljednjiPolazak() const; 
    void Ispisi() const; 
    void IsprazniKolekciju(); 
};

Polasci::Polasci(std::initializer_list<Polazak> lista_polazaka) : broj_polazaka(lista_polazaka.size()),max_broj_polazaka(lista_polazaka.size()), spisak_polazaka(new Polazak*[lista_polazaka.size()]{}){ 
    int brojac=0;
    try {
        for(int i=0; i<lista_polazaka.size(); i++) {
            spisak_polazaka[brojac++] = new Polazak(*(lista_polazaka.begin() + i));
        }
    } catch(...) {
        for(int i=0; i<=brojac; i++) {
            delete spisak_polazaka[i];
        }
        delete[] spisak_polazaka;
        throw;
    }
}

Polasci::Polasci(const Polasci &polasci) : max_broj_polazaka(polasci.max_broj_polazaka), broj_polazaka(polasci.broj_polazaka), spisak_polazaka(new Polazak*[polasci.max_broj_polazaka]{}) {
    try {
        for(int i=0; i<polasci.broj_polazaka; i++) {
            spisak_polazaka[i] = new Polazak(*polasci.spisak_polazaka[i]);
        }
    } catch(...) {
        for(int i=0; i<polasci.broj_polazaka; i++) {
            delete spisak_polazaka[i];
        }
        delete[] spisak_polazaka; //!!!!!!
        throw;
    }
}

Polasci &Polasci::operator =(const Polasci &polasci) {
    //if(max_broj_polazaka != polasci.max_broj_polazaka)throw std::logic_error("Nesaglasnan broj polazaka");
    if(&polasci == this) return *this;
    for(int i=0; i<broj_polazaka; i++) {
        delete spisak_polazaka[i];
    }
    delete[] spisak_polazaka;
    broj_polazaka = polasci.broj_polazaka;
    max_broj_polazaka = polasci.max_broj_polazaka;
    spisak_polazaka = new Polazak*[max_broj_polazaka]{};
    try {
        for(int i=0; i<broj_polazaka; i++) {
            spisak_polazaka[i] = new Polazak(*polasci.spisak_polazaka[i]);
        }
    } catch(...) {
        for(int i=0; i<broj_polazaka; i++) {
            delete spisak_polazaka[i];
        }
        delete[] spisak_polazaka;
        throw;
    }

    // if(broj_polazaka < polasci.broj_polazaka) {
    //     try {
    //         for(int i=broj_polazaka; i<polasci.broj_polazaka; i++) {
    //             spisak_polazaka[i] = new Polazak(*polasci.spisak_polazaka[i]);
    //         }
    //     } catch(...) {
    //         for(int i=broj_polazaka; i<polasci.broj_polazaka; i++) {
    //             delete spisak_polazaka[i];
    //             //spisak_polazaka[i] = nullptr;
    //         }
    //         throw;
    //     }
    // }else {
    //     for(int i=polasci.broj_polazaka; i<broj_polazaka; i++) { // bilo je < bez = !!!!!!!!!!!!!
    //         delete spisak_polazaka[i];
    //         //spisak_polazaka[i] = nullptr;
    //     }
    // }
    // max_broj_polazaka = polasci.max_broj_polazaka;
    // broj_polazaka = polasci.broj_polazaka;
    // for(int i=0; i<broj_polazaka; i++) *spisak_polazaka[i] = *polasci.spisak_polazaka[i];
    return *this;
}

Polasci::~Polasci() {
    for(int i=0; i<broj_polazaka; i++) {
        delete spisak_polazaka[i];
    }
    broj_polazaka = 0;
    delete[] spisak_polazaka;
}

Polasci::Polasci(Polasci &&polasci) : max_broj_polazaka(polasci.max_broj_polazaka), broj_polazaka(polasci.broj_polazaka) {
    spisak_polazaka = polasci.spisak_polazaka;
    polasci.spisak_polazaka = nullptr;
    polasci.broj_polazaka = 0;
}

Polasci &Polasci::operator =(Polasci &&polasci) {
    // if(max_broj_polazaka != polasci.max_broj_polazaka) {
    //     throw std::logic_error("Nesaglasan broj polazaka");
    // }
    if(this == &polasci) return *this;
    delete[] spisak_polazaka;
    spisak_polazaka = polasci.spisak_polazaka;
    polasci.spisak_polazaka = nullptr;
    max_broj_polazaka = polasci.max_broj_polazaka;
    broj_polazaka = polasci.broj_polazaka;
    polasci.max_broj_polazaka = 0;
    polasci.broj_polazaka = 0;
    return *this;
}

void Polasci::RegistrirajPolazak(std::string odrediste, std::string oznaka_voznje, int broj_perona, int sat_polaska, 
    int minute_polaska, int trajanje_voznje) {
    if(broj_polazaka >= max_broj_polazaka) {
        throw std::range_error("Dostignut maksimalni broj polazaka");
    }
    spisak_polazaka[broj_polazaka++] = new Polazak(odrediste, oznaka_voznje, broj_perona, sat_polaska, minute_polaska, trajanje_voznje);
}

void Polasci::RegistrirajPolazak(Polazak *polazak) {
    if(broj_polazaka >= max_broj_polazaka) {
        throw std::range_error("Dostignut maksimalni broj polazaka");
    }
    spisak_polazaka[broj_polazaka++] = polazak;
}

int Polasci::DajBrojPolazakaKojiKasne() const {
    return std::count_if(spisak_polazaka, (spisak_polazaka) + broj_polazaka, [] (Polazak *kasni) {
        return kasni->DaLiKasni();
    });
}

Polazak &Polasci::DajPrviPolazak() {
    auto p = *std::min_element(spisak_polazaka, spisak_polazaka+broj_polazaka, [](Polazak *p1, Polazak *p2) {
        int sati1, minute1, sati2, minute2;
        p1->OcekivanoVrijemePolaska(sati1, minute1);
        p2->OcekivanoVrijemePolaska(sati2, minute2);
        //std::cout << "\n sati1: " << sati1 << " sati2: " << sati2 
            //<< " minut1: " << minute1 << " minute2: " << minute2<<"\n";
        return (sati1 < sati2 || (sati1 == sati2 && minute1 < minute2));
    });
    return *p;
}

Polazak Polasci::DajPrviPolazak() const {
    auto p = *std::min_element(spisak_polazaka, spisak_polazaka+broj_polazaka, [](Polazak *p1, Polazak *p2) {
        int sati1, minute1, sati2, minute2;
        p1->OcekivanoVrijemePolaska(sati1, minute1);
        p2->OcekivanoVrijemePolaska(sati2, minute2);
        //std::cout << "\n sati1: " << sati1 << " sati2: " << sati2 
            //<< " minut1: " << minute1 << " minute2: " << minute2<<"\n";
        return (sati1 < sati2 || (sati1 == sati2 && minute1 < minute2));
    });
    return *p;
}

Polazak &Polasci::DajPosljednjiPolazak() {
    auto p = *std::max_element(spisak_polazaka, spisak_polazaka+broj_polazaka, [](Polazak *p1, Polazak *p2) {
        int sati1, minute1, sati2, minute2;
        p1->OcekivanoVrijemePolaska(sati1, minute1);
        p2->OcekivanoVrijemePolaska(sati2, minute2);
        return (sati1 < sati2 || (sati1 == sati2 && minute1 < minute2));
    });
    return *p;
}

Polazak Polasci::DajPosljednjiPolazak() const {
    auto p = *std::max_element(spisak_polazaka, spisak_polazaka+broj_polazaka, [](Polazak *p1, Polazak *p2) {
        int sati1, minute1, sati2, minute2;
        p1->OcekivanoVrijemePolaska(sati1, minute1);
        p2->OcekivanoVrijemePolaska(sati2, minute2);
        return (sati1 < sati2 || (sati1 == sati2 && minute1 < minute2));
    });
    return *p;
}

void Polasci::IsprazniKolekciju() {
    for(int i=0; i<broj_polazaka; i++) {
        delete spisak_polazaka[i];
    }
    broj_polazaka = 0;
}

void Polasci::Ispisi() const {
    std::cout << "\nVoznja                     Odrediste   Polazak   Dolazak   Peron";
    std::cout << "\n----------------------------------------------------------------------\n";
    std::sort(spisak_polazaka, spisak_polazaka+broj_polazaka, [](Polazak *p1, Polazak *p2) {
        int sati1, minute1, sati2, minute2;
        p1->OcekivanoVrijemePolaska(sati1, minute1);
        p2->OcekivanoVrijemePolaska(sati2, minute2);
        return (sati1 < sati2 || (sati1 == sati2 && minute1 < minute2)); 
    });
    std::for_each(spisak_polazaka, spisak_polazaka+broj_polazaka, [](Polazak *p) {
        p->Ispisi();
        std::cout << std::endl;
    });
}

int main ()
{
    Polazak p{"Merkur", "Neptun",  10,   1, 2, 2};
    p.Ispisi();
	std::cout << "\n\n";
    p.PostaviKasnjenje(60);
    p.Ispisi();
    
    Polazak p1(p);
    p.Ispisi();
	std::cout << "\n\n";
    
    Polazak pom{"Mars", "Jupiter",  10,   1, 2, 2};

    Polazak p2 = p1;
    p2 = pom;
    p.Ispisi();
	std::cout << "\n\n";
    std::cout << "\nOvdje\n";
    Polasci k{p, p1, p2, pom};
    std::cout << k.DajBrojPolazaka()<<"\n";
    std::cout << k.DajBrojPolazakaKojiKasne();
    k.Ispisi();
    k.IsprazniKolekciju();
    std::cout << "\nOvdje\n";
    std::cout << k.DajBrojPolazaka()<<"\n";
    std::cout << k.DajBrojPolazakaKojiKasne();
    k.RegistrirajPolazak("Saturn", "Jupiter", 7, 4, 5, 8);
    k.Ispisi();
    return 0;
}