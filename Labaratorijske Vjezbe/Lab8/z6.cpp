#include <iostream>
#include <cmath>

template <typename Tip>
struct Cvor {
    Tip element;
    Cvor<Tip> *veza;
};

template <typename TipElemenata>  
   Cvor<TipElemenata> *KreirajPovezanuListu(TipElemenata zavrsni);  
 
 template <typename TipElemenata> 
   int BrojElemenata(Cvor<TipElemenata> *pocetak);  
 
 template <typename TipElemenata> 
   TipElemenata SumaElemenata(Cvor<TipElemenata> *pocetak);  
 
  template <typename TipElemenata> 
   int BrojVecihOd(Cvor<TipElemenata> *pocetak, TipElemenata prag); 
 
 template <typename TipElemenata> 
   void UnistiListu(Cvor<TipElemenata> *pocetak);

int main ()
{
    std::cout << "Unesite slijed brojeva (0 za kraj): ";
    Cvor<double> *lista = KreirajPovezanuListu<double>(0);
    double arithmetic = SumaElemenata(lista) / BrojElemenata(lista);
    //std::cout << arithmetic << "\n" << SumaElemenata(lista)<<" <-suma\n" << BrojElemenata(lista)<<"\n";
    std::cout << "U slijedu ima " << BrojVecihOd<double>(lista, arithmetic) << " brojeva vecih od njihove aritmeticke sredine";
    UnistiListu(lista);
	return 0;
}

template <typename TipElemenata>  
Cvor<TipElemenata> *KreirajPovezanuListu(TipElemenata zavrsni) {
    Cvor<TipElemenata> *pocetak = nullptr, *predhodni;
    for(;;) {
        TipElemenata element;
        std::cin >> element;
        if(element == zavrsni) break;
        Cvor<TipElemenata> *novi = new Cvor<TipElemenata>{element, nullptr};
        if(!pocetak) pocetak = novi;
        else  predhodni->veza = novi;
        predhodni = novi;
    }
    return pocetak;
}

template <typename TipElemenata> 
int BrojElemenata(Cvor<TipElemenata> *pocetak) {
    auto p = pocetak;
    int br{0};
    while(p != 0) {
        br++;
        p = p->veza;
    }
    return br;
}

template <typename TipElemenata> 
TipElemenata SumaElemenata(Cvor<TipElemenata> *pocetak) {
    TipElemenata suma{};
    for(Cvor<TipElemenata> *p = pocetak; p != 0; p = p->veza) {
        suma += (*p).element;
    }
    return suma;
}

template <typename TipElemenata> 
int BrojVecihOd(Cvor<TipElemenata> *pocetak, TipElemenata prag) {
    int br{};
    while(pocetak != 0) {
        //std::cout << "\n Prag: " << prag << "\telement: " << pocetak->element;
        if(prag < pocetak->element) {
            br++;
        }
        pocetak = pocetak->veza;
    }
    return br;
}

template <typename TipElemenata> 
void UnistiListu(Cvor<TipElemenata> *pocetak) {
    while(pocetak != 0) {
        auto sljedeci = pocetak->veza;
        delete pocetak;
        pocetak = sljedeci;
    }
    delete pocetak;
}
