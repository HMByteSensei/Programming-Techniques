//TP 2022/2023: LV 10, Zadatak 2
#include <iostream>
#include <cmath>
#include <iomanip>

class Krug {
    double poluprecnik;
public:
    const double pi = 4 * atan(1);
    explicit Krug(double r) { Postavi(r); }
    void Postavi(double r) { if(r <= 0) throw std::domain_error("Neispravan poluprecnik");
    poluprecnik = r; }
    double DajPoluprecnik() const { return poluprecnik; }
    double DajObim() const { return  2*poluprecnik*pi; }
    double DajPovrsinu() const { return poluprecnik*poluprecnik*pi; }
    void Skaliraj(double faktor) { if(faktor <= 0) throw std::domain_error("Neispravan faktor skaliranja");poluprecnik *= faktor; }
    void Ispisi() const { std::cout << std::fixed << std::setprecision(5) << "R=" << DajPoluprecnik() << " O=" << DajObim() << " P=" << DajPovrsinu(); }
};

class Valjak {
    Krug baza;
    double visina;
public:
    explicit Valjak(double baza, double visina);
    void Postavi(double B, double h);
    Krug DajBazu() const { return baza; }
    double DajPoluprecnikBaze() const { return baza.DajPoluprecnik(); }
    double DajVisinu() const { return visina; }
    double DajPovrsinu() const {return 2*baza.DajPoluprecnik()*baza.pi*(baza.DajPoluprecnik() + visina);}
    double DajZapreminu() const { return DajBazu().DajPovrsinu() * visina; }
    void Skaliraj(double faktor) { if(faktor <= 0) throw std::domain_error("Neispravan faktor skaliranja"); baza.Postavi(baza.DajPoluprecnik() * faktor), visina *= faktor; }
    void Ispisi() const { std::cout << "R=" << DajPoluprecnikBaze() << " H=" << DajVisinu() << " P=" << DajPovrsinu() << " V=" << DajZapreminu(); }
};

Valjak::Valjak(double B, double h) : baza(B) {
    if(h <= 0 ) throw std::domain_error("Neispravna visina");
    visina = h;
}

void Valjak::Postavi(double B, double h) {
    baza.Postavi(B);
    if(h < 0 ) throw std::domain_error("Neispravna visina");
    visina = h;    
}

int main ()
{
    Krug k1(1);
    std::cout<<std::fixed<<std::setprecision(5)<<k1.DajPoluprecnik() << " "
    <<std::fixed<<std::setprecision(5)<< k1.DajObim() << " "
    <<std::fixed<<std::setprecision(5)<< k1.DajPovrsinu()<< std::endl;

    Krug k2(std::sqrt(2));

    std::cout <<std::fixed<<std::setprecision(5)<<k2.DajPoluprecnik() << " " 
    <<std::fixed<<std::setprecision(5)<<k2.DajObim() << " "
    <<std::fixed<<std::setprecision(5)<<k2.DajPovrsinu()<< std::endl;
	return 0;
}
