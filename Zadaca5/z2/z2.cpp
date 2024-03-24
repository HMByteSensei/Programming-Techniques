//TP 2022/2023: Zadaća 5, Zadatak 2
// Autor: Muhamed Husić
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <functional>

class Padavine {
    std::vector<int> kolicina_padavina;
    int max_vrijednost_padavine;
    void Test(double padavina) { 
        if(padavina < 0 || padavina > max_vrijednost_padavine) throw std::range_error("Ilegalna kolicina padavina");
    }
    void ImaLiPadavina() const 
        {if(kolicina_padavina.size()==0)throw std::range_error("Nema registriranih padavina");}
public:
    explicit Padavine(int max) { if(max < 0) throw std::range_error("Ilegalna maksimalna kolicina");            max_vrijednost_padavine = max;}
    void RegistrirajPadavine(double padavina) { Test(padavina); kolicina_padavina.push_back(padavina); }
    int DajBrojRegistriranihPadavina() const { return kolicina_padavina.size(); }
    void BrisiSve() { kolicina_padavina.resize(0); }
    int DajMinimalnuKolicinuPadavina() const;
    int DajMaksimalnuKolicinuPadavina() const;
    int DajBrojDanaSaPadavinamaVecimOd(double) const;
    void Ispisi() const;
    int operator[](int i) const;

    Padavine operator++(int);
    Padavine &operator++();

    friend Padavine operator +(const Padavine &p, int n);
    friend Padavine operator -(const Padavine &p, int n);
    friend Padavine operator +(int n, const Padavine &p);
    friend Padavine operator -(int n, const Padavine &p);
    friend Padavine operator -(const Padavine &p1, const Padavine &p2);

    Padavine &operator +=(int n);
    Padavine &operator -=(int n);
    Padavine &operator -=(const Padavine &p2);

    Padavine &operator -();

    bool operator ==(const Padavine &p2) const;
    bool operator !=(const Padavine &p2) const { return !((*this) == p2); }
};

int Padavine::DajMinimalnuKolicinuPadavina() const {
    ImaLiPadavina();
    return *std::min_element(kolicina_padavina.begin(), kolicina_padavina.end());
}

int Padavine::DajMaksimalnuKolicinuPadavina() const {
    ImaLiPadavina();
    return *std::max_element(kolicina_padavina.begin(), kolicina_padavina.end());
}

int Padavine::DajBrojDanaSaPadavinamaVecimOd(double n) const {
    ImaLiPadavina();
    int broj = 0;
    // std::for_each(kolicina_padavina.begin(), kolicina_padavina.end(), [&broj, n](auto p) {
    //     if(p >= n) broj++;
    // });

    // broj = std::count_if(kolicina_padavina.begin(), kolicina_padavina.end(), 
    // std::bind2nd(std::greater_equal<int>(), n));

    broj = std::count_if(kolicina_padavina.begin(), kolicina_padavina.end(),
    std::bind(std::greater<int>(), std::placeholders::_1, n));
    return broj;
}

void Padavine::Ispisi() const {
    std::vector<int> za_sortiranje = kolicina_padavina;
    std::sort(za_sortiranje.begin(), za_sortiranje.end(), std::bind(std::greater<int>(), std::placeholders::_1, std::placeholders::_2));
    std::for_each(za_sortiranje.begin(), za_sortiranje.end(), [](int x) {
        std::cout << x << std::endl;
    });
}

int Padavine::operator[](int i) const {
    if(i<=0 || i>kolicina_padavina.size()) {
        throw std::range_error("Neispravan indeks");
    }
    return kolicina_padavina[i-1];
}

Padavine Padavine::operator++(int) {
    Padavine kopija = *this;
    ++(*this);
    return kopija;
}

Padavine &Padavine::operator++() {
    // std::transform(kolicina_padavina.begin(), kolicina_padavina.end(), kolicina_padavina.begin(), std::bind1st(std::plus<int>(), 1));
    std::transform(kolicina_padavina.begin(), kolicina_padavina.end(), kolicina_padavina.begin(), std::bind(std::plus<int>(), 1, std::placeholders::_1));
    max_vrijednost_padavine++;
    return *this;
}

Padavine operator +(const Padavine &p, int n) {
    Padavine rezultat = p;
    std::transform(p.kolicina_padavina.begin(), p.kolicina_padavina.end(), rezultat.kolicina_padavina.begin(), std::bind1st(std::plus<int>(), n));
    if(std::any_of(rezultat.kolicina_padavina.begin(), rezultat.kolicina_padavina.end(), std::bind(std::less<int>(), std::placeholders::_1, 0))) {
        throw std::domain_error("Nekorektan rezultat operacije");
    }
    rezultat.max_vrijednost_padavine += n;
    return rezultat;
}

Padavine operator +(int n, const Padavine &p) {
    return p + n;
}

Padavine operator -(const Padavine &p, int n) {
    return p+(-n);
}

Padavine operator -(int n, const Padavine &p) {
    Padavine rezultat(n);
    rezultat.kolicina_padavina.resize(p.kolicina_padavina.size());
    std::transform(p.kolicina_padavina.begin(), p.kolicina_padavina.end(), rezultat.kolicina_padavina.begin(), std::bind(std::minus<int>(), n, std::placeholders::_1));
    if(std::any_of(rezultat.kolicina_padavina.begin(), rezultat.kolicina_padavina.end(), std::bind(std::less<int>(), std::placeholders::_1, 0))) {
        throw std::domain_error("Nekorektan rezultat operacije");
    }
    // citljivije razdvojiti u dva if
    if(std::any_of(rezultat.kolicina_padavina.begin(), rezultat.kolicina_padavina.end(), std::bind(std::greater<int>(), std::placeholders::_1, n))) {
        throw std::domain_error("Nekorektan rezultat operacije, padavina veca od dozvoljene");
    }
    return rezultat;
}

Padavine operator -(const Padavine &p1, const Padavine &p2) {
    int i=1; // da pozivam svoj operator []
    if(p1.kolicina_padavina.size() != p2.kolicina_padavina.size()) {
        throw std::domain_error("Nesaglasni operandi");
    }
    Padavine rezultat = p1;
    // s predavanja 5b
    std::transform(rezultat.kolicina_padavina.begin(), rezultat.kolicina_padavina.end(), 
    p2.kolicina_padavina.begin(), rezultat.kolicina_padavina.begin(), std::minus<int>());
    if(std::any_of(rezultat.kolicina_padavina.begin(), rezultat.kolicina_padavina.end(), std::bind(std::less<int>(), std::placeholders::_1, 0))) {
        throw std::domain_error("Nesaglasni operandi");
    }
    return rezultat;
}

Padavine &Padavine::operator +=(int n) {
    // mozda moze ostati u nekonzistentnom stanju
    *this = (*this) + n; //ne moze efikasnije jer svakako treba jednom kopirati
    return *this;
}

Padavine &Padavine::operator -=(int n) {
    *this = (*this) + (-n);
    return *this;
}

Padavine &Padavine::operator -=(const Padavine &p2) {
    *this = (*this) - p2;
    return *this;
}

Padavine &Padavine::operator -() {
    std::transform(kolicina_padavina.begin(), this->kolicina_padavina.end(), this->kolicina_padavina.begin(), std::bind(std::minus<int>(), max_vrijednost_padavine, std::placeholders::_1));
    return *this;
}

bool Padavine::operator ==(const Padavine &p2) const {
    if(kolicina_padavina.size() != p2.kolicina_padavina.size()) {
        return false;
    }
    return std::equal(kolicina_padavina.begin(), kolicina_padavina.end(), p2.kolicina_padavina.begin());
    //return std::all_of(kolicina_padavina.begin(), kolicina_padavina.end(), std::bind(std::equal_to<int>(), std::placeholders::_1, std::bind(&Padavine::operator[], &p2, i++)));
}

// int main ()
// {
//     Padavine p(10);
//     p.RegistrirajPadavine(2); p.RegistrirajPadavine(3); p.RegistrirajPadavine(5); p.RegistrirajPadavine(1);
//     p.RegistrirajPadavine(10); p.RegistrirajPadavine(8); p.RegistrirajPadavine(1);
//     //std::cout << p.DajBrojDanaSaPadavinamaVecimOd(1);
//     p.Ispisi();
//     std::cout << "\nDruga padavina: " << p[2] << "\n";
//     p++;
//     p.Ispisi();
//     Padavine k(20);
//     std::cout << "\nProvjera operatora -\n";
//     k = 20-p;
//     k.Ispisi();
//     //Test Padavine + Padavine
//     Padavine p1(10);
//     Padavine p2(10);
//     p1.RegistrirajPadavine(1); p1.RegistrirajPadavine(2); 
//     p2.RegistrirajPadavine(0); p2.RegistrirajPadavine(2);
//     Padavine p3 = p1 - p2;
//     // operator [] 
//     std::cout << "\np1: " << p1[1] << "\t" << p1[2] << "\np2: " << p2[1] << "\t" << p2[2];
//     std::cout << "\n";
//     std::cout << "\np3: " << p3[1] << "\t" << p3[2] << "\n";
//     p3.Ispisi();
//     std::cout << "\n" << (p1 == p2);
// 	return 0;
// }

int main() {
    {
        Padavine t(100);
        for(int i= 1; i<=10; i++)
            t.RegistrirajPadavine(i);
        t.BrisiSve();

        std::cout<<t.DajBrojRegistriranihPadavina()<<" ";

        for(int i= 50; i<=100; i++)
            t.RegistrirajPadavine(i);
        for(int i= 49; i>=1; i--)
            t.RegistrirajPadavine(i);

        std::cout<<t.DajBrojRegistriranihPadavina() << " " << t.DajMaksimalnuKolicinuPadavina()<<" "<<t.DajMinimalnuKolicinuPadavina();
    }
}