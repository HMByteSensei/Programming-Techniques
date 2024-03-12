// TP 2022/2023: Zadaća 4, Zadatak 4
// Autor: Muhamed Husić
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <map>
#include <memory>
#include <iomanip> //za globalnu funkciju IspisiOpcje koja sluzi samo za main

class Korisnik {
    int clanski_broj;
    std::string ime_prezime, adresa, broj_telefona;
public:
    Korisnik(int cl_br, std::string ime_prezime, std::string addrs, std::string br_tel) : clanski_broj(cl_br), ime_prezime(ime_prezime), adresa(addrs), broj_telefona(br_tel) {}
    int DajClanskiBroj() const { return clanski_broj; }
    std::string DajImeIPrezime() const { return ime_prezime; }
    std::string DajAdresu() const { return adresa; }
    std::string DajTelefon() const { return broj_telefona; }
    void Ispisi() {
        std::cout << "Clanski broj: " << clanski_broj << "\nIme i prezime: "<< ime_prezime << "\nAdresa: " << adresa << "\nTelefon: " << broj_telefona << std::endl;
    }
};

class Film {
    int evidenciski_broj, godina_produkcije;
    bool DVD;
    std::string ime_filma, zanr;
public:
    Korisnik *zaduzio_film = nullptr;
    Film(int evid_br, bool DVD, std::string ime_filma, std::string zanr, int g_produkcije) : evidenciski_broj(evid_br), DVD(DVD), godina_produkcije(g_produkcije), zaduzio_film(nullptr), 
    ime_filma(ime_filma), zanr(zanr) {};

    int DajEvidencijskiBroj() const { return evidenciski_broj; }
    std::string DajNaziv() const { return ime_filma; }
    std::string DajZanr() const { return zanr; }
    int DajGodinuProdukcije() const { return godina_produkcije; }
    bool DaLiJeDVD() const { return DVD; }
    void ZaduziFilm(Korisnik &k) { zaduzio_film = &k; }
    void RazduziFilm() { zaduzio_film = nullptr; }
    bool DaLiJeZaduzen() const { return (zaduzio_film != nullptr ? true : false); }
    Korisnik &DajKodKogaJe() { 
        if(zaduzio_film == nullptr) throw std::domain_error("\nFilm nije zaduzen");
        return *zaduzio_film; 
    }
    Korisnik &DajPokKodKogaJe() { return *zaduzio_film; }
    void Ispisi() const { //nema vise metoda pa sam je ovdje implementirao
        std::cout << "Evidencijski broj: " << evidenciski_broj << "\nMedij: " 
        << (DVD ? "DVD" : "Video traka") << "\nNaziv filma: " << ime_filma << "\nZanr: "
        << zanr << "\nGodina produkcije: " << godina_produkcije << std::endl;
    }
};

class Videoteka {
    std::map<int, std::shared_ptr<Korisnik>> mapa_korisnika; //clanski br i din alociran Korisnik
    std::map<int, std::shared_ptr<Film>> mapa_filmova; //eviden br filma i din aloc Film
    template <typename Tip>
        static void DubokaKopija(const std::map<int, std::shared_ptr<Tip>> &mapa_neceg, 
        std::map<int, std::shared_ptr<Tip>> &izmjeni);
    template <typename Tip>
        static void ZaPomjeranje(std::map<int, std::shared_ptr<Tip>> &iz, std::map<int, std::shared_ptr<Tip>> &pomjeri_u);
public:
    Videoteka() = default;

    Videoteka(const Videoteka &kopija);
    Videoteka &operator =(const Videoteka &v);
    Videoteka(Videoteka &&kopija);
    Videoteka &operator =(Videoteka &&v);

    void RegistrirajNovogKorisnika(int cl_br, std::string ime_prezime, std::string addrs, std::string br_tel); 
    void RegistrirajNoviFilm(int evid_br, bool DVD, std::string ime_filma, std::string zanr, int g_produkcije);

    Korisnik &NadjiKorisnika(int cl_broj) const;
    Film &NadjiFilm(int evid_broj) const ;

    void IzlistajKorisnike() const;
    void IzlistajFilmove() const;
    void ZaduziFilm(int evidenciski_br_filma, int clanski_broj);
    void RazduziFilm(int evid_broj_filma);
    void PrikaziZaduzenja(int clanski_broj_korisnika) const;
};

//------------------STATIK-----------------------------
template <typename Tip>
void Videoteka::DubokaKopija(const std::map<int, std::shared_ptr<Tip>> &mapa_neceg, std::map<int, std::shared_ptr<Tip>> &izmjeni ) {
    for(auto it = izmjeni.begin(); it != izmjeni.end();) {
        it = izmjeni.erase(it);     
    }

    for(auto it = mapa_neceg.begin(); it != mapa_neceg.end(); it++) {
        std::shared_ptr<Tip> objekt = std::make_shared<Tip>(*it->second);
        izmjeni.insert({it->first, objekt});
    }
}
template <typename Tip>
void Videoteka::ZaPomjeranje(std::map<int, std::shared_ptr<Tip>> &iz_MAPE, std::map<int, std::shared_ptr<Tip>> &pomjeri_u) {
    for(auto it = pomjeri_u.begin(); it != pomjeri_u.end();) {
        it = pomjeri_u.erase(it);
    }

    for(auto it = iz_MAPE.begin(); it != iz_MAPE.end(); it++) {
        pomjeri_u.insert(std::make_pair(it->first, std::move(it->second)));
    }

    for(auto it = iz_MAPE.begin(); it != iz_MAPE.end();) {
        it = iz_MAPE.erase(it);
    }
}
//-----------------------------------------------------

Videoteka::Videoteka(const Videoteka &kopija) {
    Videoteka::DubokaKopija(kopija.mapa_korisnika, mapa_korisnika);
    Videoteka::DubokaKopija(kopija.mapa_filmova, mapa_filmova);
}

Videoteka &Videoteka::operator =(const Videoteka &v) {
    Videoteka::DubokaKopija(v.mapa_korisnika, mapa_korisnika);
    Videoteka::DubokaKopija(v.mapa_filmova, mapa_filmova);
    return *this;
}

Videoteka::Videoteka(Videoteka &&kopija) {
    Videoteka::ZaPomjeranje(kopija.mapa_korisnika, mapa_korisnika);
    Videoteka::ZaPomjeranje(kopija.mapa_filmova, mapa_filmova);
}

Videoteka &Videoteka::operator =(Videoteka &&v) {
    Videoteka::ZaPomjeranje(v.mapa_korisnika, mapa_korisnika);
    Videoteka::ZaPomjeranje(v.mapa_filmova, mapa_filmova);
    return *this;
}

void Videoteka::RegistrirajNovogKorisnika(int cl_br, std::string ime_prezime, std::string addrs, std::string br_tel) {
    if(!mapa_korisnika.empty() && mapa_korisnika.end() != mapa_korisnika.find(cl_br)) {
        throw std::logic_error("Vec postoji korisnik s tim clanskim brojem");
    }
    mapa_korisnika.insert({cl_br, std::make_shared<Korisnik>(cl_br, ime_prezime, addrs, br_tel)});
}

void Videoteka::RegistrirajNoviFilm(int evid_br, bool DVD, std::string ime_filma, std::string zanr, int g_produkcije) {
    if(!mapa_filmova.empty() && mapa_filmova.end() != mapa_filmova.find(evid_br)) {
        throw std::logic_error("Film s tim evidencijskim brojem vec postoji");
    }
    mapa_filmova.insert({evid_br, std::make_shared<Film>(evid_br, DVD, ime_filma, zanr, g_produkcije)});
}

Korisnik &Videoteka::NadjiKorisnika(int cl_broj) const {
    auto it = mapa_korisnika.find(cl_broj);
    if(it == mapa_korisnika.end()) {
        throw std::logic_error("Korisnik nije nadjen");
    }
    return *it->second;
}

Film &Videoteka::NadjiFilm(int evid_broj) const {
    auto it = mapa_filmova.find(evid_broj);
    if(it == mapa_filmova.end()) {
        throw std::logic_error("Film nije nadjen");
    }
    return *(it->second);
}

void Videoteka::IzlistajKorisnike() const {
    int drugi_red = 1;
    for(auto it = mapa_korisnika.begin(); it != mapa_korisnika.end(); it++) {
        drugi_red++;
        it->second->Ispisi();
        if(drugi_red == 2) {
            drugi_red = 1;
            std::cout << std::endl;
        }
    }
}

void Videoteka::IzlistajFilmove() const {
    int drugi_red = 1;
    for(auto it = mapa_filmova.begin(); it != mapa_filmova.end(); it++) {
        drugi_red++;
        it->second->Ispisi();

        if((it->second)->DaLiJeZaduzen()) {
            std::cout << std::endl << "Zaduzen kod korisnika: " 
            << it->second->DajPokKodKogaJe().DajImeIPrezime() << " (" 
            << it->second->DajPokKodKogaJe().DajClanskiBroj() << ")";            
        }
        if(drugi_red == 2) {
            drugi_red = 1;
            std::cout << std::endl;
        }
    }
}

void Videoteka::ZaduziFilm(int evidenciski_br_filma, int clanski_broj) {
    Film& film_za_evidentirati = NadjiFilm(evidenciski_br_filma);
    Korisnik& korisnik_za_evidentirati = NadjiKorisnika(clanski_broj);
    if(film_za_evidentirati.DaLiJeZaduzen()) {
        throw std::logic_error("Film vec zaduzen");
    }
    //std::cout << "\nKorisnik: " <<korisnik_za_evidentirati.DajImeIPrezime() << "\tfilm: " << film_za_evidentirati.DajNaziv()<<"\n\n\n";
    film_za_evidentirati.ZaduziFilm(korisnik_za_evidentirati);
    //std::cout << "\nZaduzio: " << film_za_evidentirati.zaduzio_film->DajImeIPrezime()<<"\n";
}

void Videoteka::RazduziFilm(int evid_broj_filma) {
    Film &film_za_razduziti = NadjiFilm(evid_broj_filma);
    if(!film_za_razduziti.DaLiJeZaduzen()) {
        throw std::logic_error("Film nije zaduzen");
    }
    film_za_razduziti.RazduziFilm();
}

void Videoteka::PrikaziZaduzenja(int clanski_broj_korisnika) const {
    Korisnik korisnik_id = NadjiKorisnika(clanski_broj_korisnika);
    int drugi_red = 0;
    bool zaduzio_je_knjigu = false;
    for(auto it = mapa_filmova.begin(); it != mapa_filmova.end(); it++) {
        try {
            auto kod_koga_je = it->second->DajKodKogaJe();
            if(clanski_broj_korisnika == kod_koga_je.DajClanskiBroj()) {
                zaduzio_je_knjigu = true;
                drugi_red++;
                it->second->Ispisi();
                if(drugi_red == 2) {
                    drugi_red = 0;
                    std::cout << std::endl;
                }
            }
        } catch(...) {}
    }
    if(!zaduzio_je_knjigu) {
        std::cout << "Korisnik nema zaduzenja!";
    }
}

//---------------------------OVO SAMO ZA MAIN------------------------------
void IspisOpcija() {
    std::cout << std::left << std::setw(30) << "Naziv akcije/opcije" << std::setw(10) << std::right << "Opcija\n";
    std::cout << std::setw(39) << std::setfill('-') << "";
    std::cout << std::setfill(' ');
    std::cout << std::left << std::setw(30) << "\nRegistrirajNovogKorisnika" << std::setw(10) << std::right << "(1)";
    std::cout << std::left << std::setw(30) << "\nRegistrirajNoviFilm" << std::setw(10) << std::right << "(2)";
    std::cout << std::left << std::setw(30) << "\nNadjiKorisnika" << std::setw(10) << std::right << "(3)";
    std::cout << std::left << std::setw(30) << "\nNadjiFilm" << std::setw(10) << std::right << "(4)";
    std::cout << std::left << std::setw(30) << "\nIzlistajKorisnike" << std::setw(10) << std::right << "(5)";
    std::cout << std::left << std::setw(30) << "\nIzlistajFilmove" << std::setw(10) << std::right << "(6)";
    std::cout << std::left << std::setw(30) << "\nZaduziFilm" << std::setw(10) << std::right << "(7)";
    std::cout << std::left << std::setw(30) << "\nRazduziFilm" << std::setw(10) << std::right << "(8)";
    std::cout << std::left << std::setw(30) << "\nPrikaziZaduzenja" << std::setw(10) << std::right << "(9)";
    std::cout << std::left << std::endl;
}

// svi potrebni parametri
void Unesi(int &evid_br, bool &DVD, std::string &ime_filma, std::string &zanr_adresa, int &gProdukcije, std::string &broj_tel) {
        if(evid_br != 0) {
            std::cout << "Unesi evidencijski/clanski broj: "; std::cin >> evid_br;
            std::cin.clear(); std::cin.ignore(1000, '\n');
        }
        if(DVD != false) {
            std::cout << "Ako je CD unesite 1, inace 0: "; std::cin >> DVD;
            DVD = (DVD == true);
            std::cin.clear(); std::cin.ignore(1000, '\n');
        }
        if(ime_filma != "") {
            std::cout << "Unesi ime i prezime korisnika / ime filma: ";
            std::getline(std::cin, ime_filma);
        }
        if(zanr_adresa != "") {
            std::cout << "Unesi zanr/adresu: ";
            std::getline(std::cin, zanr_adresa);
        }
        if(gProdukcije != 0) {
            std::cout << "\nUnesi g produkcije / clanski broj: "; std::cin >> gProdukcije;
            std::cin.clear(); std::cin.ignore(1000, '\n');
        }
        if(broj_tel != "") {
            std::cout << "Unesi broj telefona: ";
            std::getline(std::cin, broj_tel);
        }
    }
//-------------------------------------------------------------------------

int main() {
    Videoteka v;

    // "magicne konstante" su samo da se razlikuju od variabli koje sluze za signalizaciju da nema unosa
    int opcija, clanski_evid_br = 1, gProd = 1; 
    bool DVD = true;
    std::string ime = "1", zanr_adresa = "1", brTel = "1";

    int NB = 0; // ne unosi se broj kod trenutne opcije
    std::string NS = ""; // ne unosi se string
    bool Nbool = false; // isto
    while(true) {
        std::cout << "\nUnesite zeljenu opciju(0 - izlaz, 10 - ispis opcija, [1, 9] - opcija): ";
        std::cin >> opcija;
        //std::cin.ignore(1000, '\n');
        if(opcija == 0) break;
        else if(opcija == 10) IspisOpcija();
        if(!std::cin || (opcija <0 && opcija >10)) {
            std::cout << "Neispravan unos!";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            opcija = -1;
        } else {
            if(opcija != 10) {
                std::cout << "Unesite potrebne podatke:\n";
                switch(opcija) {
                    case 1:
                        Unesi(clanski_evid_br, Nbool, ime, zanr_adresa, NB, brTel);
                        v.RegistrirajNovogKorisnika(clanski_evid_br, ime, zanr_adresa, brTel);
                        break;
                    case 2:
                        Unesi(clanski_evid_br, DVD, ime, zanr_adresa, gProd, NS);
                        v.RegistrirajNoviFilm(clanski_evid_br, DVD, ime, zanr_adresa, gProd);
                        break;
                    case 3:
                        Unesi(clanski_evid_br, Nbool, NS, NS, NB, NS);
                        v.NadjiKorisnika(clanski_evid_br);
                        break;
                    case 4:
                        Unesi(clanski_evid_br, Nbool, NS, NS, NB, NS);
                        v.NadjiFilm(clanski_evid_br);
                        break;
                    case 5:
                        v.IzlistajKorisnike();
                        break;
                    case 6:
                        v.IzlistajFilmove();
                        break;
                    case 7:
                        Unesi(clanski_evid_br, Nbool, NS, NS, gProd, NS);
                        v.ZaduziFilm(clanski_evid_br, gProd);
                        break;
                    case 8:
                        Unesi(clanski_evid_br, Nbool, NS, NS, NB, NS);
                        v.RazduziFilm(clanski_evid_br);
                        break;
                    case 9:
                        Unesi(clanski_evid_br, Nbool, NS, NS, NB, NS);
                        v.PrikaziZaduzenja(clanski_evid_br);
                        break;
                    default:
                        std::cout << "Neispravan unos!";
                        std::cin.clear();
                        std::cin.ignore(1000, '\n');
                        break;
                }
            }
        }
    }
}