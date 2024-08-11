//TP 2022/2023: LV 9, Zadatak 1
#include <iostream>
#include <cmath>
#include <tuple>
#include <array>

class Vektor3d {
    std::array<double, 3> koordinate;
    mutable int broj_ispisa = 0;
public:
    void Postavi(double x, double y, double z) { Vektor3d::koordinate.at(0) = x; Vektor3d::koordinate.at(1) = y; Vektor3d::koordinate.at(2) = z; }
    void Ocitaj(double &x, double &y, double &z) const { x = this->koordinate[0]; y = this->koordinate[1]; z = this->koordinate[2]; }
    void Ispisi() const { std::cout << "{" << koordinate[0] << "," << koordinate[1] << "," << koordinate[2] << "}"; broj_ispisa++; }
    double DajX() const { return koordinate[0]; }
    double DajY() const { return koordinate[1]; }
    double DajZ() const { return koordinate[2]; }
    double DajDuzinu() const { return std::sqrt(koordinate[0]*koordinate[0] + koordinate[1]*koordinate[1] + koordinate[2]*koordinate[2]); }
    Vektor3d &PomnoziSaSkalarom(double s);
    Vektor3d &SaberiSa(const Vektor3d &v);
    void PostaviX(double x) { Vektor3d::koordinate[0] = x; }
    void PostaviY(double y) { Vektor3d::koordinate[1] = y; }
    void PostaviZ(double z) { Vektor3d::koordinate[2] = z; }

    int DajBrojIspisa() const { return broj_ispisa; }

    friend Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2);
};

Vektor3d & Vektor3d::PomnoziSaSkalarom(double s) {
    koordinate[0]  *= s, koordinate[1] *= s, koordinate[2] *= s;
    return *this;   
}

Vektor3d & Vektor3d::SaberiSa(const Vektor3d &v) {
    koordinate[0] += v.koordinate[0];
    koordinate[1] += v.koordinate[1];
    koordinate[2] += v.koordinate[2];
    return *this;
}

Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2) {
    std::tuple<double, double, double> v1_1{v1.koordinate[0], v1.koordinate[1], v1.koordinate[2]};
    std::tuple<double, double, double> v2_2{v2.koordinate[0], v2.koordinate[1], v2.koordinate[2]};
    double x, y, z;
    x = std::get<0>(v1_1) + std::get<0>(v2_2);
    y = std::get<1>(v1_1) + std::get<1>(v2_2);
    z = std::get<2>(v1_1) + std::get<2>(v2_2);
    Vektor3d v3;
    v3.Postavi(x, y, z);
    return v3;
}

std::tuple<double, double, double> Unesi(int i) {
    std::cout << "Unesite koordinate vektora3d v" << i << ": ";
    double x, y, z;
    std::cin >> x >> y >> z;
    std::tuple<double, double, double> t{x,y,z};
    return t;
}
int main () {
    Vektor3d v1;
    double x,y,z;
    std::tie(x,y,z) = Unesi(1);
    v1.Postavi(x,y,z);

    Vektor3d v2;
    std::tie(x,y,z) = Unesi(2);
    v2.Postavi(x,y,z);

    std::cout << "Vasi vektori su v1: ";
    v1.Ispisi();
    std::cout << ", a vektor v2: ";
    v2.Ispisi();
    std::cout << "\nNjihov zbir je: ";
    ZbirVektora(v1, v2).Ispisi();
    std::cout << "\nPomnozen s 10 v1 iznosi: ";
    v1.PomnoziSaSkalarom(10).Ispisi();
    std::cout << ", a v2: ";
    v2.PomnoziSaSkalarom(10).Ispisi();

    v1.Ispisi();
    std::cout << "\nIspis nad v1 je primjenjen " << v1.DajBrojIspisa() << " puta, a na v2 " << v2.DajBrojIspisa();
	return 0;
}
