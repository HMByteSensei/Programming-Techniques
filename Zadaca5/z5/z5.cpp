// Autor: Muhamed Husić
#include <iostream>
#include <cmath>
#include <fstream>
#include <functional>
#include <vector>
#include <string>

template <typename TipElemenata>
class DatotecniKontejner {
    std::fstream tok;
    void TOK() { tok.clear(); if(!tok) throw std::logic_error("Probemi prilikom pristupa datoteci"); }
public:
    DatotecniKontejner(const std::string &ime_datoteke);
    void DodajNoviElement(const TipElemenata &element);
    int DajBrojElemenata();
    TipElemenata DajElement(int pozicija);
    void IzmijeniElement(int pozicija, const TipElemenata &element);
    void Sortiraj(std::function<bool(const TipElemenata &, const TipElemenata &)>
    kriterij = std::less<TipElemenata>());
};

template <typename Tip>
DatotecniKontejner<Tip>::DatotecniKontejner(const std::string &ime_datoteke) {
    tok.open(ime_datoteke, std::ios::in | std::ios::out | std::ios::binary);
    if(!tok) {
        tok.clear();
        tok.open(ime_datoteke, std::ios::binary | std::ios::out);
        if(!tok) {
            throw std::logic_error("Problemi prilikom otvaranja ili kreiranja datoteke"); 
        }
        tok.close();
        tok.open(ime_datoteke, std::ios::in | std::ios::out | std::ios::binary);
    }
}

template <typename Tip>
void DatotecniKontejner<Tip>::DodajNoviElement(const Tip &element) {
    TOK();
    tok.seekp(0, std::ios::end);
    tok.write(reinterpret_cast<const char*>(&element), sizeof(Tip));
    tok.flush();
}

template <typename Tip>
int DatotecniKontejner<Tip>::DajBrojElemenata() {
    TOK();
    int trenutno = tok.tellg();
    tok.seekg(0, std::ios::end);
    int duzina = tok.tellg();
    tok.seekg(trenutno, std::ios::beg);
    return duzina / sizeof(Tip);
}

template <typename Tip>
Tip DatotecniKontejner<Tip>::DajElement(int pozicija) {
    TOK();
    if(pozicija < 0 || pozicija >= DajBrojElemenata()) {
        throw std::range_error("Neispravna pozicija");
    }
    tok.seekg(pozicija * sizeof(Tip), std::ios::beg);
    Tip element;
    tok.read(reinterpret_cast<char*>(&element), sizeof element);

    tok.flush();
    return element;
}

template <typename Tip>
void DatotecniKontejner<Tip>::IzmijeniElement(int pozicija, const Tip &element) {
    TOK();
    if(pozicija < 0 || pozicija >= DajBrojElemenata()) {
        throw std::range_error("Neispravna pozicija");
    }
    tok.seekp(pozicija * sizeof(Tip));
    tok.write(reinterpret_cast<const char*>(&element), sizeof element);
}

template <typename Tip>
void DatotecniKontejner<Tip>::Sortiraj(std::function<bool(const Tip &, const Tip &)>kriterij)  {
    TOK();
    Tip element1, element2, temp;
    int poz;
    for(int i=0; i<DajBrojElemenata()-1; i++) {
        int pozicija = i * sizeof(Tip);
        tok.seekg(pozicija, std::ios::beg);
        tok.read(reinterpret_cast<char*>(&element1), sizeof element1);
        int j = i+1;
        poz = j;
        bool promjena = false; // nije doslo do promjene redoslijeda elemenata
        temp = element1;
        while(tok.read(reinterpret_cast<char*>(&element2), sizeof element2)) {
            //std::cout << "\nITERACIJA" << j-1 <<"\n";
            //std::cout << "\nElement1: " << element1 << "   Element2: " << element2;
            if(kriterij(element2, element1)) {
                //std::cout << "\n\n\t\tKRITERI = TACNO\n";
                element1 = element2;
                poz = j;
                promjena = true;
                //std::cout << "Element1: " << element1 << "   Element2: " << element2 << " temp: " << temp;
            }
            j++;
        }
        //std::cout << "\n\t\t\t\tKRAJ\n";
        tok.clear();
        if(promjena) {
            tok.seekp(pozicija, std::ios::beg);
            tok.write(reinterpret_cast<char*>(&element1), sizeof(Tip));
            tok.seekp(poz*sizeof(Tip), std::ios::beg);
            tok.write(reinterpret_cast<char*>(&temp), sizeof(Tip));
        }
    }
    tok.flush();
}

// int main ()
// {
//     DatotecniKontejner<double> dk1("TEST.DAT");
//     for(int i=0 ; i < 10; i++)
//         dk1.DodajNoviElement(i);
//     std::cout<<"\n\tElementi niz: ";
//     for(int i=0 ; i < 10; i++)
//         std::cout<<dk1.DajElement(i)<<" ";
//     std::cout << "\nSortirano: ";
//     dk1.Sortiraj();
//     for(int i=0; i<10; i++) {
//         std::cout << dk1.DajElement(i) << " ";
//     }
// 	return 0;
// }

int main() {
    DatotecniKontejner<int> dk1("ime5.DAT");
        DatotecniKontejner<int> dk2("ime5.DAT");
        DatotecniKontejner<int> dk3("ime6.DAT");
        
        dk1.DodajNoviElement(1);
                
        dk2.DodajNoviElement(1);
        
        std::cout<<dk1.DajBrojElemenata()<<" "<<dk2.DajBrojElemenata()<<" "<<dk3.DajBrojElemenata()<<std::endl;
        
        std::cout<<sizeof(dk2);
        return 0;
}