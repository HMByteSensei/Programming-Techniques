//TP 2022/2023: LV 10, Zadatak 4
#include <iostream>
#include <cmath>
#include <iomanip>

const double pi = 4 * atan(1);

class Ugao {
    double radijani;
    double ProvjeraUgla(double radijan);
public:
    Ugao(double radijani = 0) { Postavi(radijani); }
    Ugao(int stepeni, int minute, int sekunde) { Postavi(stepeni, minute, sekunde); }  
    void Postavi(double radijani); 
    void Postavi(int stepeni, int minute, int sekunde); 
    double DajRadijane() const { return radijani; } 
    void OcitajKlasicneJedinice(int &stepeni, int &minute, int &sekunde); 
    int DajStepene() const { return DajRadijane() * (180 / pi); } 
    int DajMinute() const { return (DajRadijane() * (180 / pi) - DajStepene()) * 60; } 
    int DajSekunde() const { return static_cast<int>(DajRadijane() * (180*3600) / pi) % 60; } 
    void Ispisi() const {std::cout << std::fixed << std::setprecision(5) << DajRadijane(); }
    void IspisiKlasicno() const {std::cout << DajStepene() << "deg " << DajMinute() << "min " << DajSekunde() << "sec";}
    Ugao &SaberiSa(const Ugao &u);
    Ugao &PomnoziSa(double x); 
    friend Ugao ZbirUglova(const Ugao &u1, const Ugao &u2); 
    friend Ugao ProduktUglaSaBrojem(const Ugao &u, double x);
};

Ugao ZbirUglova(const Ugao &u1, const Ugao &u2) {
    return { u1.DajRadijane() + u2.DajRadijane() };
}

Ugao ProduktUglaSaBrojem(const Ugao &u, double x) {
    return { x * u.DajRadijane() };
}

Ugao& Ugao::PomnoziSa(double x) {
    Postavi(ProvjeraUgla(x * DajRadijane()));
    return *this;
}
 
Ugao& Ugao::SaberiSa(const Ugao &u) {
    Postavi(ProvjeraUgla(u.DajRadijane() + this->DajRadijane()));
    return *this;
}

void Ugao::OcitajKlasicneJedinice(int &stepen, int &minute, int &sekunde) {
    stepen = DajRadijane() * (180 / pi);
    minute = (DajRadijane() * (180 / pi) - stepen) * 60;
    sekunde = (((DajRadijane() * (180 / pi) - stepen) * 60) - minute) * 60;
}

void Ugao::Postavi(int s, int m, int sekunde) {
    radijani = ProvjeraUgla((s + m/60. + sekunde/3600.) * (pi / 180));
}

double Ugao::ProvjeraUgla(double r) {
    while(r >= 2*pi) r -= 2*pi; 
    while(r < 0) r+=2*pi;
    return r;
}

void Ugao::Postavi(double r) {
    radijani = ProvjeraUgla(r);
}

int main ()
{
    Ugao u,v;
    u.Postavi(212, 57, 28.062), v.Postavi(1,1,-1);
    u.Ispisi(); std::cout << std::endl;
    u.IspisiKlasicno(); std::cout << std::endl;
    v.Ispisi(); std::cout << std::endl;
    v.IspisiKlasicno();;
	return 0;
}
