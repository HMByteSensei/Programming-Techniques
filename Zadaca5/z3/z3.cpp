//TP 2022/2023: Zadaća 5, Zadatak 3
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <fstream>

class ApstraktnoVozilo {
    int tezina_vozila;
public:
    ApstraktnoVozilo(int t) : tezina_vozila(t) {}
    virtual ~ApstraktnoVozilo() {}
    int DajTezinu() const { return tezina_vozila; }
    virtual int DajUkupnuTezinu() const = 0;
    virtual ApstraktnoVozilo *DajKopiju() const = 0;
    virtual void IspisiPodatke() const = 0;
};

class Automobil : public ApstraktnoVozilo {
    std::vector<int> tezina_putnika;
    friend std::ostream &operator <<(std::ostream &tok, const ApstraktnoVozilo &v);
public:
    Automobil(int tezina, std::vector<int> t) : ApstraktnoVozilo(tezina), tezina_putnika(t) {}
    int DajUkupnuTezinu() const override;
    ApstraktnoVozilo *DajKopiju() const override { return new Automobil(*this); }
    void IspisiPodatke() const override;
};

class Kamion : public ApstraktnoVozilo {
    int tezina_tereta;
    friend std::ostream &operator <<(std::ostream &tok, const ApstraktnoVozilo &v);

public:
    Kamion(int tezina, int t) : ApstraktnoVozilo(tezina), tezina_tereta(t) {}
    int DajUkupnuTezinu() const override { return DajTezinu() + tezina_tereta; }
    ApstraktnoVozilo *DajKopiju() const override { return new Kamion(*this); }
    void IspisiPodatke() const override;
};

class Autobus : public ApstraktnoVozilo {
    int broj_putnika, prosjecna_tezina;
    friend std::ostream &operator <<(std::ostream &tok, const ApstraktnoVozilo &v);
public:
    Autobus(int tezina, int br_putnika, int pros_tez) : ApstraktnoVozilo(tezina), broj_putnika(br_putnika), prosjecna_tezina(pros_tez) {}
    int DajUkupnuTezinu() const override { return broj_putnika * prosjecna_tezina + DajTezinu(); }
    ApstraktnoVozilo *DajKopiju() const override { return new Autobus(*this); }
    void IspisiPodatke() const override;
};

class Vozilo {
    ApstraktnoVozilo *vozilo;
    void Test() const { if(!vozilo) throw std::logic_error("Nespecificirano vozilo!"); }
public:
    Vozilo() : vozilo(nullptr) {}
    Vozilo(const ApstraktnoVozilo &a) : vozilo(a.DajKopiju()) {}
    ~Vozilo() { delete vozilo; }
    
    int DajUkupnuTezinu() const { Test(); return vozilo->DajUkupnuTezinu(); }
    ApstraktnoVozilo *DajKopiju() const { Test(); return vozilo->DajKopiju(); }
    void IspisiPodatke() const { Test(); vozilo->IspisiPodatke(); }
    
    Vozilo(const Vozilo &v) { if(!v.vozilo) vozilo = nullptr; else vozilo = v.vozilo->DajKopiju();  }
    Vozilo &operator=(const Vozilo &v) {
        if(v.vozilo == nullptr) vozilo = nullptr; 
        else {delete vozilo; vozilo = v.vozilo->DajKopiju();}
        return *this;
    }

    Vozilo(Vozilo &&v) { std::swap(vozilo, v.vozilo); }
    Vozilo &operator =(Vozilo &&v) { std::swap(vozilo, v.vozilo); return *this; }

    friend std::istream &operator >>(std::istream &tok, Vozilo &v);
    friend std::ostream &operator <<(std::ostream &tok, const Vozilo &v);
};

//-------------------------------------------------------------------------
int Automobil::DajUkupnuTezinu() const {
    int zbir{};
    std::for_each(tezina_putnika.begin(), tezina_putnika.end(), [&zbir](auto x) {
        zbir += x;
    });
    return zbir + DajTezinu();
}

void Automobil::IspisiPodatke() const { 
    std::cout << "\nVrsta vozila: Automobil\nVlastita tezina: "
    << DajTezinu() << " kg\nTezine putnika: ";
    for(int i=0; i<tezina_putnika.size(); i++) {
        std::cout << tezina_putnika.at(i) << " kg";
        if(i!=tezina_putnika.size() - 1) std::cout << ", ";
    }
    std::cout << "\nUkupna tezina: " << DajUkupnuTezinu() << " kg"; 
}

void Kamion::IspisiPodatke() const {
    std::cout << "\nVrsta vozila: Kamion\nVlastita tezina: " << DajTezinu() << " kg\nTezina tereta: " 
    << tezina_tereta << " kg\nUkupna tezina: " << DajUkupnuTezinu() << " kg";
}

void Autobus::IspisiPodatke() const {
    std::cout << "\nVrsta vozila: Autobus\nVlastita tezina: " << DajTezinu() << " kg\nBroj putnika: "
    << broj_putnika << "\nProsjecna tezina putnika: " << prosjecna_tezina << " kg\nUkupna tezina: "
    << DajUkupnuTezinu() << " kg";
}

std::istream &operator >>(std::istream &tok, Vozilo &v) {
    char linija;
    tok.get(linija);
    int tezina{};
    if(linija == 'A') {
        tok >> tezina;
        std::vector<int> tezina_putnika;
        int br;
        while(tok >> br) {
            tezina_putnika.push_back(br);
        }
        tok.clear();
        v = (Automobil(tezina, tezina_putnika));
    }
    else if(linija == 'K') {
        int br, tezina_t;
        tok >> br >> tezina_t;
        tok.ignore(1000, '\n');
        v = (Kamion(br, tezina_t));
    }
    else if(linija == 'B') {
        int tezina_b, br_put, pros_tez_put;
        tok >> tezina_b >> br_put >> pros_tez_put;
        tok.ignore(1000, '\n');
        v = (Autobus(tezina_b, br_put, pros_tez_put));
    }
    return tok;
}

std::ostream &operator <<(std::ostream &tok, const ApstraktnoVozilo &v) {
    if(const Automobil * automobil = dynamic_cast<const Automobil*>(&v)) {
        tok << "A" << automobil->DajTezinu() << "\t";
        for(int tezina_put : automobil->tezina_putnika) {
            tok << tezina_put << "  ";
        }
    }
    if(const Autobus * bus = dynamic_cast<const Autobus*>(&v)) {
        tok << "B" << bus->DajTezinu() << "  " << bus->broj_putnika << "  " << bus->prosjecna_tezina; 
    }
    if(const Kamion *k = dynamic_cast<const Kamion*>(&v)) {
        tok << "K" << k->DajTezinu() << "  " << k->tezina_tereta;
    }
    return tok;
}

//za vozilo operator <<
std::ostream &operator <<(std::ostream &tok, const Vozilo &v) {
    //v.IspisiPodatke();
    
    tok << v.DajUkupnuTezinu() << std::endl;

    // za upis u datoteku
    // if(typeid(&v) == typeid(Automobil)) {
    //     tok << "\nVrsta vozila: Automobil\nVlastita tezina: ";
    // }
    // else if(typeid(&v) == typeid(Autobus)) {
    //     tok << "\nVrsta vozila: Autobus\nVlastita tezina: ";
    // }
    // else {
    //     tok << "\nVrsta vozila: Kamion\nVlastita tezina: ";
    // }
    // tok << v.vozilo->DajTezinu() << " kg\n";
    // tok << "Ukupna tezina: " << v.DajUkupnuTezinu() << " kg"; 
    
    return tok;
}
//-------------------------------------------------------------------------

int main ()
{
    std::ifstream ulazni_tok("VOZILA.TXT");
    if(!ulazni_tok) {
        std::cout << "Datoteka ne postoji!";
        return 0;
    }
    std::vector<Vozilo> vektor;
    Vozilo element;
    while(ulazni_tok >> element) {
        vektor.push_back(element);
    }
    ulazni_tok.close();
    // for(int i=0; i<vektor.size(); i++) {
    //     std::cout << vektor[i] << std::endl;
    // }
    // Automobil aa(100, {6,7,8});
    // Kamion k(1232, 238905);
    // Autobus a(10, 2, 3);
    // std::cout << a << "\t" << k << "\t" << aa;

    std::vector<int> v_tezine(vektor.size());
    for(int i=0; i<v_tezine.size(); i++) {
        v_tezine[i] = i;
    }

    std::sort(v_tezine.begin(), v_tezine.end(), [&vektor](int v1, int v2) {
        return vektor[v1].DajUkupnuTezinu() < vektor[v2].DajUkupnuTezinu();
    });

    for(int i=0; i<vektor.size(); i++) {
        std::cout << vektor[v_tezine[i]];
    }
    // std::ofstream izlazni_tok("SortiranaVozila.txt");
    // for(Vozilo v : vektor) {
    //     izlazni_tok << v;
    // }
    // izlazni_tok.close();
	return 0;
}