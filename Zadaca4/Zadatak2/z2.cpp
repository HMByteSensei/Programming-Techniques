// TP 2022/2023: Zadaća 4, Zadatak 4
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <memory>
#include <vector>
#include <algorithm>
#include <iomanip>

using PAR = std::pair<double, double>;

class NepreklapajuciKrug {
  double poluprecnik;
  std::pair<double, double> centar;
  const double pi = 4 * atan(1);
  static constexpr double epsilon = 1e-10;
  NepreklapajuciKrug *veza{};
  static NepreklapajuciKrug *posljednji;
  static void TestPoluprecnika(double r) {
    if (r < 0)
      throw std::domain_error("Nedozvoljen poluprecnik");
  }
  static bool PribliznoJednako(double x, double y) { return (std::abs(x-y) <= epsilon * (std::abs(x) + std::abs(y))); }
  static bool PribliznoJednako(PAR x, PAR y) { return (PribliznoJednako(x.first, y.first) && PribliznoJednako(x.second, y.second)); }
  static bool ManjeJednako(double x, double y) { return ( x < y || PribliznoJednako(x, y) ); }
  static bool DaLiSePreklapaju(const NepreklapajuciKrug &k1, const NepreklapajuciKrug &k2);
  void Podudarnost(std::pair<double, double> stari_centar, double stari_poluprecnik);
public:
  explicit NepreklapajuciKrug(double poluprecnik = 0);
  explicit NepreklapajuciKrug(const std::pair<double, double> &centar, double poluprecnik = 0);
  ~NepreklapajuciKrug();
  NepreklapajuciKrug(const NepreklapajuciKrug &) = delete;
  NepreklapajuciKrug &operator =(const NepreklapajuciKrug &) = delete;
  std::pair<double, double> DajCentar() const { return centar; }
  double DajPoluprecnik() const { return poluprecnik; }
  double DajObim() const { return 2 * poluprecnik * pi; }
  double DajPovrsinu() const { return poluprecnik * poluprecnik * pi; }
  NepreklapajuciKrug &PostaviCentar(const std::pair<double, double> &centar);
  NepreklapajuciKrug &PostaviPoluprecnik(double poluprecnik);
  void Ispisi() const { std::cout << "{(" << DajCentar().first << ","<< DajCentar().second << "),"<< DajPoluprecnik()<<"}\n"; }
  NepreklapajuciKrug &Transliraj(double delta_x, double delta_y);
  NepreklapajuciKrug &Rotiraj(double alpha);
  NepreklapajuciKrug &Rotiraj(const std::pair<double, double> &centar_rotacije, double alpha);
  static double RastojanjeCentara(const NepreklapajuciKrug &k1, const NepreklapajuciKrug &k2);
  
  bool DaLiSadrzi(const NepreklapajuciKrug &k) const{ return ManjeJednako(RastojanjeCentara(*this, k), (this->DajPoluprecnik() - k.DajPoluprecnik())); } 

  static NepreklapajuciKrug * DajPosljednji() { return posljednji; }
  NepreklapajuciKrug * DajVezu() { return veza; }
};

NepreklapajuciKrug* NepreklapajuciKrug::posljednji = nullptr;

NepreklapajuciKrug::~NepreklapajuciKrug() {
    if(posljednji == this) {
        posljednji = posljednji->veza;
    } else {
        auto pok = posljednji;
        auto iza_pok = posljednji;
        while(pok != nullptr) {
            if(pok == this) {
                iza_pok->veza = pok->veza;
                //delete pok; sada niko ne pokazuje na pok
                break;
            }
            if(pok != posljednji) {
                iza_pok = iza_pok->veza;
            }
            pok = pok->veza;        
        }
    }
}


NepreklapajuciKrug::NepreklapajuciKrug(double poluprecnik) { 
    TestPoluprecnika(poluprecnik);
    NepreklapajuciKrug::poluprecnik = poluprecnik;
    centar.first = 0, centar.second = 0;
    veza = posljednji;
    posljednji = this;
    for(auto pok = veza; pok != nullptr; pok = (*pok).veza) {
        if(pok != this && DaLiSePreklapaju(*pok, *posljednji)) {
            throw std::logic_error("Nedozvoljeno preklapanje");
        }
    }
}

NepreklapajuciKrug::NepreklapajuciKrug(const std::pair<double, double> &centar, double poluprecnik) {
    TestPoluprecnika(poluprecnik);
    NepreklapajuciKrug::centar.first = centar.first;
    NepreklapajuciKrug::centar.second = centar.second;
    NepreklapajuciKrug::poluprecnik = poluprecnik;
    veza = posljednji;
    posljednji = this;
    // if(veza != nullptr){
    //     std::cout << "\nVeza:\n";
    //     veza->Ispisi();}
    // std::cout << "\nPosljednji:\n";
    // posljednji->Ispisi();
    // std::cout << "\n\n";
    for(auto pok = posljednji; pok != nullptr; pok = pok->veza) { // pok = veza!!!!!!!!!!!!
        if(this != pok && DaLiSePreklapaju(*pok, *posljednji)) {
            posljednji = veza;
            throw std::logic_error("Nedozvoljeno preklapanje");
        }
    }
}

NepreklapajuciKrug& NepreklapajuciKrug::PostaviPoluprecnik(double poluprecnik) {
    TestPoluprecnika(poluprecnik);
    double stari_r = NepreklapajuciKrug::poluprecnik;
    NepreklapajuciKrug::poluprecnik = poluprecnik;
    for(auto pok = posljednji; pok != nullptr; pok = (*pok).veza) {
        if(pok != this && DaLiSePreklapaju(*pok, *posljednji)) {
            // Brise izmjene
            NepreklapajuciKrug::poluprecnik = stari_r;
            throw std::logic_error("Nedozvoljeno preklapanje");
        }
    }
    return *this;
}

NepreklapajuciKrug& NepreklapajuciKrug::PostaviCentar(const std::pair<double, double> &centar) { 
    double stari_x = NepreklapajuciKrug::centar.first;
    double stari_y = NepreklapajuciKrug::centar.second;
    NepreklapajuciKrug::centar.first = centar.first; 
    NepreklapajuciKrug::centar.second = centar.second;
    for(auto pok = posljednji; pok != nullptr; pok = (*pok).veza) {
        if(this != pok && DaLiSePreklapaju(*pok, *posljednji)) {
            // Brise izmjene
            NepreklapajuciKrug::centar.first = stari_x;
            NepreklapajuciKrug::centar.second = stari_y;
            throw std::logic_error("Nedozvoljeno preklapanje");
        }
    }
    return *this; 
}

NepreklapajuciKrug& NepreklapajuciKrug::Rotiraj(const std::pair<double, double> &centar_rotacije, double alpha) {
    alpha *= pi / 180;
    PAR stari_centar = centar;
    double stari_poluprecnik=poluprecnik;
    
    centar.first = centar_rotacije.first + (centar.first - centar_rotacije.first) * std::cos(alpha) - (centar.second - centar_rotacije.second) *     std::sin(alpha);

    centar.second = centar_rotacije.second + (stari_centar.first - centar_rotacije.first) * std::sin(alpha) + (centar.second -centar_rotacije.second) * std::cos(alpha);
    for(auto pok = posljednji; pok != nullptr; pok = pok->veza) {
        if(pok != this && DaLiSePreklapaju(*pok, *posljednji)) {
            centar.first = stari_centar.first;
            centar.second = stari_centar.second;
            poluprecnik = stari_poluprecnik;
            throw std::logic_error("Nedozvoljeno preklapanje");
        }
    }
    return *this;
}

NepreklapajuciKrug& NepreklapajuciKrug::Rotiraj(double alpha) {
    alpha *= pi/180;
    PAR stari_centar = centar;
    double stari_poluprecnik = poluprecnik;
    centar.first = centar.first * std::cos(alpha) - centar.second * std::sin(alpha);
    centar.second = stari_centar.first * std::sin(alpha) + std::cos(alpha) * centar.second;
    for(auto pok = posljednji; pok != nullptr; pok = pok->veza) {
        if(pok != this && DaLiSePreklapaju(*pok, *posljednji)) {
            centar.first = stari_centar.first;
            centar.second = stari_centar.second;
            poluprecnik = stari_poluprecnik;
            throw std::logic_error("Nedozvoljeno preklapanje");
        }
    }
    return *this;    
}

double NepreklapajuciKrug::RastojanjeCentara(const NepreklapajuciKrug &k1, const NepreklapajuciKrug &k2) {
    return std::sqrt( (k2.DajCentar().first - k1.DajCentar().first) * (k2.DajCentar().first - k1.DajCentar().first) + 
                        (k2.DajCentar().second - k1.DajCentar().second) * (k2.DajCentar().second - k1.DajCentar().second) );
}

bool NepreklapajuciKrug::DaLiSePreklapaju(const NepreklapajuciKrug &k1, const NepreklapajuciKrug &k2) {
    std::pair<double, double> veci_manji = (k1.DajPoluprecnik() > k2.DajPoluprecnik() ? 
                std::make_pair(k1.DajPoluprecnik(), k2.DajPoluprecnik()) : 
                std::make_pair(k2.DajPoluprecnik(), k1.DajPoluprecnik()));
    // ako je rastojanje izmedju centara <= (veci - manji) poluprecnik onda se NepreklapajuciKrugovi nalaze jedan u drugom
    return ((RastojanjeCentara(k1, k2) < (k1.DajPoluprecnik() + k2.DajPoluprecnik())) || ManjeJednako(RastojanjeCentara(k1, k2), (veci_manji.first - veci_manji.second)) || PribliznoJednako(RastojanjeCentara(k1, k2), (k1.DajPoluprecnik() + k2.DajPoluprecnik())));
}

void NepreklapajuciKrug::Podudarnost(std::pair<double, double> stari_centar, double stari_poluprecnik) {
    for(auto pok = posljednji; pok != nullptr; pok = pok->veza) {
        if(pok != posljednji && DaLiSePreklapaju(*pok, *posljednji)) {
            centar.first = stari_centar.first;
            centar.second = stari_centar.second;
            poluprecnik = stari_poluprecnik;
            throw std::logic_error("Nedozvoljeno preklapanje");
        }
    }
}

NepreklapajuciKrug &NepreklapajuciKrug::Transliraj(double delta_x, double delta_y) { 
    centar.first += delta_x; 
    centar.second += delta_y; 
    for(auto pok = posljednji; pok != nullptr; pok = pok->veza) {
        if(pok != posljednji && DaLiSePreklapaju(*pok, *posljednji)) {
            centar.first -= delta_x;
            centar.second -= delta_y;
            throw std::logic_error("Nedozvoljeno preklapanje");
        }
    }
    return *this; 
}

int main() {
    int n;
    std::cout << "Unesite broj krugova: ";
    while(true) {
        std::cin >> n;
        if(n < 1) {
            std::cout << "Neispravan broj krugova, unesite ponovo! ";
            std::cin.clear();
        } else {
            std::cin.ignore(1000, '\n');
            break;
        }
        std::cin.ignore(1000, '\n');
    }
    std::vector<std::shared_ptr<NepreklapajuciKrug>> krugovi(n);
    try {
        std::pair<double, double> koordinate;
        double poluprecnik;
        for(int i=0; i<n; i++) {
            std::cout << "Unesite centar za " << i+1 << ". krug: ";
            bool pogresan_unos = true;
            while(pogresan_unos) {
                std::cin >> koordinate.first >> koordinate.second;
                if(!std::cin) {
                    std::cout << "Neispravan centar!";
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    std::cout << "\nUnesite ponovo centar za " << i+1 << ". krug: ";
                } else pogresan_unos = false;
            }
            std::cout << "Unesite poluprecnik: ";
            bool petlja = true;
            while(petlja) {
                try {
                    std::cin >> poluprecnik;
                    if(!std::cin) {
                        std::cin.clear();
                        std::cin.ignore(1000, '\n');
                        poluprecnik = -1;
                    }
                    krugovi[i] = (std::make_shared<NepreklapajuciKrug>(koordinate, poluprecnik));
                    petlja = false;
                } catch(std::domain_error e) {
                    std::cout << "Neispravan poluprecnik!" << std::endl;
                    std::cout << "Unesite ponovo poluprecnik za "<< i+1 << ". krug: ";
                } catch(std::logic_error e) {
                    std::cout << e.what() << std::endl;
                    i--;
                    break;
                }
            }
        }

        // std::cout << "Unesite element koji zelite mijenjati: ";
        // int br;
        // std::cin >> br;
        // std::cin.ignore(1000, '\n');
        // std::cout << "Unesite koordinate " << br << ". NepreklapajuciKruga: ";
        // std::cin >> koordinate.first >> koordinate.second;
        // std::cout << "Unesite poluprecnik: ";
        // std::cin >> poluprecnik;
        // try {
        //     krugovi.at(br-1)->PostaviCentar(koordinate);
        // } catch(std::domain_error e) {
        //     std::cout << e.what() << std::endl;
        // } catch(std::logic_error e) {
        //     std::cout << e.what() << std::endl;
        // }
        // for(auto pok=NepreklapajuciKrug::DajPosljednji(); pok!=nullptr; pok=pok->DajVezu()) {
        //     pok->Ispisi();
        //     std::cout << "\n";
        // }

        // SORTIRANJE
        std::cout << "Krugovi nakon obavljenog sortiranja:\n";
        std::sort(krugovi.begin(), krugovi.end(), [](std::shared_ptr<NepreklapajuciKrug> p1, std::shared_ptr<NepreklapajuciKrug> p2) {
            return (p1->DajPovrsinu() > p2->DajPovrsinu() || 
            (p1->DajPovrsinu() == p2->DajPovrsinu() && (p1->DajCentar().first > p2->DajCentar().first) || (p1->DajCentar().first == p2->DajCentar().first && p1->DajCentar().second > p2->DajCentar().second)));
        });
        std::for_each(krugovi.begin(), krugovi.end(), [](std::shared_ptr<NepreklapajuciKrug> p1) {
            p1->Ispisi();
            std::cout << "\n";
        });
    } catch(std::bad_alloc e) {
        std::cout << "Nedovoljno memorije!" <<std::endl;
    }

    return 0;
}