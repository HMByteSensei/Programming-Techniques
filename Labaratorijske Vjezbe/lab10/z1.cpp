//TP 2022/2023: LV 10, Zadatak 1
#include <iostream>
#include <cmath>
#include <stdexcept>

class StedniRacun {
    double stanje_racuna;
public:
    StedniRacun(double broj = 0);
    void Ulozi(double iznos) { 
        if(stanje_racuna + iznos < 0) throw std::logic_error("Transakcija odbijena");
        stanje_racuna += iznos; 
    }
    void Podigni(double iznos);
    double DajStanje() const { return stanje_racuna; }
    void ObracunajKamatu(double kam_stop_u_procentia) { 
        if(kam_stop_u_procentia < 0) throw std::logic_error("Nedozvoljena kamatna stopa");
        stanje_racuna += stanje_racuna * kam_stop_u_procentia / 100;
    }
};

StedniRacun::StedniRacun(double broj) {
    if(broj < 0) {
        throw std::logic_error("Nedozvoljeno pocetno stanje");
    }
    stanje_racuna = broj;
}

void StedniRacun::Podigni(double iznos) {
    if(iznos > stanje_racuna) throw std::logic_error("Transakcija odbijena");
    stanje_racuna -= iznos;
}

int main ()
{
    const StedniRacun konstantni_racun(1);
    std::cout << konstantni_racun.DajStanje() << "\n";
    std::cout << "\nUnesite stanje racuna: ";
    double br;
    std::cin >> br;
    StedniRacun racun(br);
    std::cout << "\nStanje racuna: " << racun.DajStanje() << "\n";
    
	return 0;
}
