//TP 2022/2023: LV 9, Zadatak 1
#include <iostream>
#include <cmath>
#include <tuple>

class Vektor3d {
    double x, y, z;
public:
    void Postavi(double x, double y, double z) { Vektor3d::x = x; Vektor3d::y = y; Vektor3d::z = z; }
    void Ocitaj(double &x, double &y, double &z) const { x = this->x; y = this->y; z = this->z; }
    void Ispisi() const { std::cout << "{" << x << "," << y << "," << z << "}"; }
    double DajX() const { return x; }
    double DajY() const { return y; }
    double DajZ() const { return z; }
    double DajDuzinu() const { return std::sqrt(x*x + y*y + z*z); }
    Vektor3d &PomnoziSaSkalarom(double s);
    Vektor3d &SaberiSa(const Vektor3d &v);
    void PostaviX(double x) { Vektor3d::x = x; }
    void PostaviY(double y) { Vektor3d::y = y; }
    void PostaviZ(double z) { Vektor3d::z = z; }

    friend Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2);
};

Vektor3d & Vektor3d::PomnoziSaSkalarom(double s) {
    x  *= s, y *= s, z *= s;
    return *this;   
}

Vektor3d & Vektor3d::SaberiSa(const Vektor3d &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2) {
    std::tuple<double, double, double> v1_1{v1.x, v1.y, v1.z};
    std::tuple<double, double, double> v2_2{v2.x, v2.y, v2.z};
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
	return 0;
}
