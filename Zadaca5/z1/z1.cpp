//TP 2022/2023: Zadaća 5, Zadatak 1
#include <iostream>
#include <cmath>
#include <tuple>


using TROJKA = std::tuple<double, double, double>; 

class Sinusoida {
    double amplituda, frekvencija, faza;
    const double PI = 4 * std::atan(1);
    void Normaliziraj(double amplituda, double frekvencija, double faza);
    void NormalizirajBezPromjene();
public:
    Sinusoida(double A, double f, double FI) { Normaliziraj(A, f, FI); }
    double DajAmplitudu() const { return amplituda; }
    double DajFrekvenciju() const { return frekvencija; }
    double DajFazu() const { return faza; }
    TROJKA DajParametre() const { return std::make_tuple(amplituda, frekvencija, faza); }
    Sinusoida &PostaviAmplitudu(double A) { Normaliziraj(A, frekvencija, faza); return *this; }
    Sinusoida &PostaviFrekvenciju(double f) { Normaliziraj(amplituda, f, faza); return *this; }
    Sinusoida &PostaviFazu(double FI) { Normaliziraj(amplituda, frekvencija, FI); return *this; }
    Sinusoida &PostaviParametre(TROJKA t) { Normaliziraj(std::get<0>(t), std::get<1>(t), std::get<2>(t)); return *this; }
    
    friend Sinusoida operator +(const Sinusoida &t1, const Sinusoida &t2);
    friend Sinusoida operator -(const Sinusoida &t1, const Sinusoida &t2);
    Sinusoida &operator -() { amplituda = -amplituda; Normaliziraj(amplituda, frekvencija, faza); return *this; }
    Sinusoida operator *(double n) const;
    Sinusoida operator /(double n) const;

    friend Sinusoida operator +(const Sinusoida &t1, const Sinusoida &t2);
    friend Sinusoida operator -(const Sinusoida &t1, const Sinusoida &t2);

    Sinusoida &operator +=(const Sinusoida &t2);
    Sinusoida &operator -=(const Sinusoida &t2);
    Sinusoida &operator *=(double n);
    Sinusoida &operator /=(double n);

    double &operator[](std::string kljuc);
    const double &operator[](std::string kljuc) const;
    double operator()(double t);

    Sinusoida &operator =(const Sinusoida &s1);
    //Sinusoida &operator =(Sinusoida &&s1);
};

Sinusoida &Sinusoida::operator =(const Sinusoida &s1) {
    amplituda = s1.amplituda;
    frekvencija = s1.frekvencija;
    faza = s1.faza;
    return *this;
}

void TestFrekvencija(const Sinusoida &t1, const Sinusoida &t2) { 
    if(t1.DajFrekvenciju() != t2.DajFrekvenciju()) 
        throw std::domain_error("Razlicite frekvencije"); 
}

void Sinusoida::Normaliziraj(double amplituda, double frekvencija, double faza) {
    if(amplituda < 0) {
        amplituda = -amplituda;
        faza += PI;
    }
    if(frekvencija < 0) {
        frekvencija = -frekvencija;
        faza = -faza + PI;
    }
    while(faza > PI) {
        faza -= 2*PI;
    }
    while(faza < -PI) {
        faza += 2*PI;
    }
    this->amplituda = amplituda;
    this->frekvencija = frekvencija;
    this->faza = faza;
}

void Sinusoida::NormalizirajBezPromjene() {
    if(amplituda < 0) {
        amplituda = -amplituda;
        faza += PI;
    }
    if(frekvencija < 0) {
        frekvencija = -frekvencija;
        faza = -faza + PI;
    }
    while(faza > PI) {
        faza -= 2*PI;
    }
    while(faza < -PI) {
        faza += 2*PI;
    }
}

Sinusoida operator +(const Sinusoida &t1, const Sinusoida &t2) {
    TestFrekvencija(t1, t2);
    Sinusoida s = t1;
    s.amplituda = s.amplituda + t2.amplituda;
    s.faza = s.faza + t2.faza;
    //s.NormalizirajBezPromjene();
    const double PI = 4*atan(1);
    while(s.faza > PI) {
        s.faza -= 2*PI;
    }
    while(s.faza < -PI) {
        s.faza += 2*PI;
    }
    return s;
}

Sinusoida operator -(const Sinusoida &t1, const Sinusoida &t2) {
    TestFrekvencija(t1, t2);
    Sinusoida s = t1;
    s.amplituda -= t2.amplituda;
    s.faza -= t2.faza;
    s.NormalizirajBezPromjene();
    return s;
}

Sinusoida Sinusoida::operator *(double n) const { 
    Sinusoida kopija = *this;
    kopija.amplituda *= n; 
    kopija.NormalizirajBezPromjene();
    return kopija; 
}

Sinusoida Sinusoida::operator /(double n) const { 
    Sinusoida kopija = *this;
    kopija.amplituda /= n; 
    kopija.NormalizirajBezPromjene();
    return kopija;
}

Sinusoida operator *(double n, const Sinusoida &s) {
    return s*n;
}

Sinusoida operator /(double n, const Sinusoida &s) {
    return s/n;
}

Sinusoida &Sinusoida::operator +=(const Sinusoida &t2) {
    TestFrekvencija(*this, t2);
    amplituda += t2.amplituda;
    faza += t2.faza;
    Normaliziraj(amplituda, frekvencija, faza);
    return *this;
}

Sinusoida &Sinusoida::operator -=(const Sinusoida &t2) {
    TestFrekvencija(*this, t2);
    amplituda -= t2.amplituda;
    faza -= t2.faza;
    Normaliziraj(amplituda, frekvencija, faza);
    return *this;
}
Sinusoida &Sinusoida::operator *=(double n) {
    amplituda *= n; 
    Normaliziraj(amplituda, frekvencija, faza);
    return *this; 
}

Sinusoida &Sinusoida::operator /=(double n) {
    amplituda /= n; 
    Normaliziraj(amplituda, frekvencija, faza);
    return *this; 
}

double &Sinusoida::operator[](std::string kljuc) {
    if(kljuc == "A") return amplituda;
    else if(kljuc == "omega" || kljuc == "w") return frekvencija;
    else if(kljuc == "phi" || kljuc == "fi") return faza;
    else throw std::domain_error("Neispravan naziv parametra");
}

const double &Sinusoida::operator[](std::string kljuc) const {
    if(kljuc == "A") return amplituda;
    else if(kljuc == "omega" || kljuc == "w") return frekvencija;
    else if(kljuc == "phi" || kljuc == "fi") return faza;
    else throw std::domain_error("Neispravan naziv parametra");
}

double Sinusoida::operator()(double t) {
    return amplituda * std::sin((frekvencija * t) + faza);
}

int main ()
{
    std::cout << "Unesite parametre sinusoide: ";
    double A, f, FI;
    std::cin >> A >> f >> FI;
    //std::cin >> std::ws;
    Sinusoida s(A, f, FI);
    std::cout << "\nUnesite vrijeme: ";
    double t;
    std::cin >> t;
    std::cout << "\nU trenutku " << t << " vrijednost sinusoide je: " << s(t);
    std::cout << "\nAmplituda * (frekvencija * t + faza), gdje je amplituda: " << s["A"] << " frekvencija: "
    << s["w"] << " faza: " << s["fi"];

	return 0;
}