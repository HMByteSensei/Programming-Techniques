// TP 2022/2023: Zadaća 4, Zadatak 4
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <algorithm>

#include <vector>

using PAR = std::pair<double, double>;
const double pi = 4 * atan(1);

class Krug {
  double poluprecnik;
  std::pair<double, double> centar;
  static constexpr double epsilon = 1e-10;
  static void TestPoluprecnika(double r) {
    if (r < 0)
      throw std::domain_error("Nedozvoljen poluprecnik");
  }
  static bool PribliznoJednako(double x, double y) { return (std::abs(x-y) <= epsilon * (std::abs(x) + std::abs(y))); }
  static bool PribliznoJednako(PAR x, PAR y) { return (PribliznoJednako(x.first, y.first) && PribliznoJednako(x.second, y.second)); }
  static bool ManjeJednako(double x, double y) { return ( x < y || PribliznoJednako(x, y) ); }
public:
  explicit Krug(double poluprecnik = 0) { PostaviPoluprecnik(poluprecnik); centar.first = 0, centar.second = 0; }
  explicit Krug(const std::pair<double, double> &centar, double poluprecnik = 0) { PostaviPoluprecnik(poluprecnik); PostaviCentar(centar); }
  std::pair<double, double> DajCentar() const { return centar; }
  double DajPoluprecnik() const { return poluprecnik; }
  double DajObim() const { return 2 * poluprecnik * pi; }
  double DajPovrsinu() const { return poluprecnik * poluprecnik * pi; }
  Krug &PostaviCentar(const std::pair<double, double> &centar);
  Krug &PostaviPoluprecnik(double poluprecnik);
  void Ispisi() const { std::cout << "{(" << DajCentar().first << ","<< DajCentar().second << "),"<< DajPoluprecnik()<<"}"; }
  Krug &Transliraj(double delta_x, double delta_y) { 
      centar.first += delta_x; 
      centar.second += delta_y; 
      return *this; 
    }
  Krug &Rotiraj(double alpha);
  Krug &Rotiraj(const std::pair<double, double> &centar_rotacije, double alpha);
  static double RastojanjeCentara(const Krug &k1, const Krug &k2);
  static bool DaLiSuIdenticni(const Krug &k1, const Krug &k2) {
      return (PribliznoJednako(k1.DajCentar(), k2.DajCentar()) && PribliznoJednako(k1.DajPoluprecnik(), k2.DajPoluprecnik()));
    }
  static bool DaLiSuPodudarni(const Krug &k1, const Krug &k2) { return PribliznoJednako(k1.DajPoluprecnik(), k2.DajPoluprecnik()); }
  static bool DaLiSuKoncentricni(const Krug &k1, const Krug &k2) { return PribliznoJednako(k1.DajCentar(), k2.DajCentar()); }
  static bool DaLiSeDodirujuIzvani(const Krug &k1, const Krug &k2);
  static bool DaLiSeDodirujuIznutri(const Krug &k1, const Krug &k2);
  static bool DaLiSePreklapaju(const Krug &k1, const Krug &k2);
  static bool DaLiSeSijeku(const Krug &k1, const Krug &k2){
      if((k1.DaLiSadrzi(k2) || k2.DaLiSadrzi(k1))) return false;
      return (RastojanjeCentara(k1, k2) < k1.DajPoluprecnik() + k2.DajPoluprecnik());}
  bool DaLiSadrzi(const Krug &k) const{ return ManjeJednako(RastojanjeCentara(*this, k), (this->DajPoluprecnik() - k.DajPoluprecnik())); } 
  friend Krug TransliraniKrug(const Krug &k, double delta_x, double delta_y);
  friend Krug RotiraniKrug(const Krug &k, double alpha);
  friend Krug RotiraniKrug(const Krug &k, const std::pair<double, double> &centar_rotacije, double alpha);
};

Krug& Krug::PostaviPoluprecnik(double poluprecnik) {
    TestPoluprecnika(poluprecnik);
    Krug::poluprecnik = poluprecnik;
    return *this;
}

Krug& Krug::PostaviCentar(const std::pair<double, double> &centar) { 
    Krug::centar.first = centar.first; 
    Krug::centar.second = centar.second; 
    return *this; 
}

Krug& Krug::Rotiraj(const std::pair<double, double> &centar_rotacije, double alpha) {
    //alpha *= pi/180;
    double rot_x, rot_y;
    rot_x = centar_rotacije.first + (centar.first - centar_rotacije.first) * std::cos(alpha) - (centar.second - centar_rotacije.second) * std::sin(alpha);

    rot_y = centar_rotacije.second + (centar.first - centar_rotacije.first) * std::sin(alpha) + (centar.second -centar_rotacije.second) * std::cos(alpha);
    centar.first = rot_x;
    centar.second = rot_y;
    return *this;
}

Krug& Krug::Rotiraj(double alpha) {
    //alpha *= pi/180;
    double rx, ry;
    rx = centar.first * std::cos(alpha) - centar.second * std::sin(alpha);
    ry = centar.first * std::sin(alpha) + centar.second * std::cos(alpha);
    centar.first = rx;
    centar.second = ry;
    return *this;    
}

double Krug::RastojanjeCentara(const Krug &k1, const Krug &k2) {
    return std::sqrt( (k2.DajCentar().first - k1.DajCentar().first) * (k2.DajCentar().first - k1.DajCentar().first) + 
    (k2.DajCentar().second - k1.DajCentar().second) * (k2.DajCentar().second - k1.DajCentar().second) );
}

bool Krug::DaLiSeDodirujuIzvani(const Krug &k1, const Krug &k2) {
    // Krugovi se dodiruju sa spoljasnje strane akko je rastojanje njihovih centara jednaka zbiru polulprecnika
    return PribliznoJednako(RastojanjeCentara(k1, k2), (k1.DajPoluprecnik() + k2.DajPoluprecnik()));
}

bool Krug::DaLiSeDodirujuIznutri(const Krug &k1, const Krug &k2) {
    // ako su im isti poluprecnici, onda se krugovi ne mogu sa unutrasnje strane dodirivati u jednoj tacki
    if(DaLiSuPodudarni(k1, k2)) return false;
    std::pair<double, double> veci_manji = (k1.DajPoluprecnik() > k2.DajPoluprecnik() ? 
                std::make_pair(k1.DajPoluprecnik(), k2.DajPoluprecnik()) : 
                std::make_pair(k2.DajPoluprecnik(), k1.DajPoluprecnik()));
    return PribliznoJednako(veci_manji.first, veci_manji.second + RastojanjeCentara(k1, k2));
}

bool Krug::DaLiSePreklapaju(const Krug &k1, const Krug &k2) {
    std::pair<double, double> veci_manji = (k1.DajPoluprecnik() > k2.DajPoluprecnik() ? 
                std::make_pair(k1.DajPoluprecnik(), k2.DajPoluprecnik()) : 
                std::make_pair(k2.DajPoluprecnik(), k1.DajPoluprecnik()));
    // ako je rastojanje izmedju centara <= (veci - manji) poluprecnik onda se krugovi nalaze jedan u drugom
    return (DaLiSeSijeku(k1, k2) || ManjeJednako(RastojanjeCentara(k1, k2), (veci_manji.first - veci_manji.second)));
}

Krug TransliraniKrug(const Krug &k, double delta_x, double delta_y) {
    Krug novi(k.DajCentar(), k.DajPoluprecnik());
    return novi.Transliraj(delta_x, delta_y);
}

Krug RotiraniKrug(const Krug &k, double alpha) {
    Krug novi(k.DajCentar(), k.DajPoluprecnik());
    return novi.Rotiraj(alpha);
}

Krug RotiraniKrug(const Krug &k, const std::pair<double, double> &centar_rotacije, double alpha) {
    Krug novi(k.DajCentar(), k.DajPoluprecnik());
    return novi.Rotiraj(centar_rotacije, alpha);
}

int main() {
    std::cout << "Unesite broj krugova: ";
    int n;
    std::cin >> n;
    if(n < 1) {
        std::cout << "Uneseni broj nije prirodan!";
        return 0;
    }
    std::cin.ignore(1000, '\n');
    Krug **krugovi = nullptr;
    try {
        krugovi = new Krug*[n]{};
        std::pair<double, double> koordinate;
        double poluprecnik;
        for(int i=0; i<n; i++) {
            try {
                std::cout << "Unesite centar " << i+1 << ". kruga: ";
                std::cin >> koordinate.first >> koordinate.second;
                if(!std::cin) {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    throw std::logic_error("Neispravne koordinate centra! Pokusajte ponovo:\n");
                }
                std::cout << "Unesite poluprecnik " << i+1 << ". kruga: ";
                std::cin >> poluprecnik;
                krugovi[i] = new Krug(koordinate, poluprecnik);
                //poluprecnik *= (4*atan(1))/180;
            } catch(std::domain_error e) {
                std::cout << "Neispravan poluprecnik!" << " Pokusajte ponovo:" << std::endl;
                i--;
            } catch(std::logic_error e) {
                std::cout << e.what() << std::endl;
                i--;
            }
        }
    } catch(std::bad_alloc e) {
        std::cout << "Problemi sa alokacijom memorije!" <<std::endl;
        return 0;
    }

    std::cout << "Unesite parametre translacije (delta_x,delta_y): ";
    int delta_x, delta_y;
    std::cin >> delta_x >> delta_y;
    std::transform(krugovi, krugovi+n, krugovi, [delta_x, delta_y](Krug *k) {
        k->PostaviCentar({delta_x+k->DajCentar().first, delta_y+k->DajCentar().second});
        return k;
    });
    std::cout << "Unesite ugao rotacije oko tacke (0,0) u stepenima: ";
    int ugao;
    std::cin >> ugao;
    const double pi = 4 * atan(1);
    // nema smisla rotirati kad je ugao rotacije 0
    if(ugao != 0) {
        double radius = ugao * pi / 180; 
        std::transform(krugovi, krugovi+n, krugovi, [radius](Krug *k) {
            k->Rotiraj(std::make_pair<double>(0,0),radius);
            return k;
        });
    }
    
    std::cout << "Parametri krugova nakon obavljene transformacije su:\n";
    std::sort(krugovi, krugovi+n, [](Krug *k1, Krug *k2) {
        return k1->DajPovrsinu() < k2->DajPovrsinu();
    });
    std::for_each(krugovi, krugovi+n, [](Krug* k) {
        k->Ispisi();
        std::cout << std::endl;
    });

    std::cout << "Krug sa najvecim obimom je: ";
    auto najveci_obim = *std::max_element(krugovi, krugovi+n, [](Krug *k1, Krug *k2) {
        return k1->DajObim() < k2->DajObim();
    });
    najveci_obim->Ispisi();
    std::cout << "\n";
    int presjecanje = 0;
    int start=0;
    static const double epsilon = 10e-10;
    std::for_each(krugovi, krugovi+n, [&krugovi, n, &presjecanje, &start](Krug *k1) {
        std::for_each(krugovi+start, krugovi+n, [&k1, &presjecanje](Krug *k2) {
            double y = k1->DajPoluprecnik() + k2->DajPoluprecnik();
            double x1 = Krug::RastojanjeCentara(*k1, *k2);
            if(k1 != k2 && !(k1->DaLiSadrzi(*k2) || k2->DaLiSadrzi(*k1)) || Krug::DaLiSeDodirujuIznutri(*k1,*k2)) // ovo daLSedodiruju iznutra je zbog toga sto AT 3 ne valja presjecaju se 2 kruga a jedan se dodiruje iznutra
                if(x1 < y || (std::abs(x1-y) == epsilon * (std::abs(x1) + std::abs(y)))) {
                    std::cout << "Presjecaju se krugovi:\n";
                    k1->Ispisi();
                    std::cout << " i ";
                    k2->Ispisi();
                    std::cout << "\n";
                    presjecanje++;
                    //std::cout << "\n\tRastojanje: " << x1 << "\tzbir r: " << y << "\n";
                }
        });
        start++;
    });
    if(presjecanje == 0) {
        std::cout << "Ne postoje krugovi koji se presjecaju!";
    }

    // std::for_each(krugovi, krugovi+n, [] (Krug *k) {
    //     k->Ispisi();
    //     std::cout << std::endl;
    // });

    for(int i=0; i<n; i++) {
        delete krugovi[i];
    }
    delete[] krugovi;
    return 0;
}