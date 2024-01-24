// grid[10][30] je pocetna vrijednost robota
//TP 2022/2023: Zadaća 2, Zadatak 1
#include <iostream>
#include <cmath>
#include <algorithm>
#include <array>
#include <string>

// string je koristen samo za ispis tabele

enum class Pravci {Sjever, Sjeveroistok, Istok, Jugoistok, Jug, Jugozapad, Zapad, Sjeverozapad};
enum class KodoviGresaka {PogresnaKomanda, NedostajeParametar, SuvisanParametar, NeispravanParametar};
enum class Komande {Idi, Rotiraj, Sakrij, Otkrij, PrikaziTeren, Kraj};

std::array<std::array<char, 61>, 21> grid{};
bool vidljivost{true};

void Idi(int &x, int &y, Pravci orijentacija, int korak); 
void Rotiraj(Pravci &orijentacija, int ugao); 
void PostaviVidljivost(bool vidljiv); 
void IspisiPoziciju(int x, int y, Pravci orijentacija); 
void PrikaziTeren(); 
void PrijaviGresku(KodoviGresaka kod_greske); 
void IzvrsiKomandu(Komande komanda, int parametar, int &x, int &y, Pravci &orijentacija); 

bool UnosKomande(Komande &komanda, int &parametar, KodoviGresaka &kod_greske);

int main () {
    // postavljanje robota i ostalih parametara
    grid.at(10).at(30) = 'O';
    Pravci orijentacija = Pravci::Sjever;
    int x{0}, y{0}, parametar{0}; // parametar je broj koraka ili ugao
    Komande komanda = Komande::Idi; // za svaki slucaj inicijaliziramo je na neku komandu
    KodoviGresaka kod_greske;
    bool doslo_do_greske{false};
    while(komanda != Komande::Kraj) {
        if(komanda != Komande::PrikaziTeren && komanda != Komande::Kraj) {
            if(!doslo_do_greske) {
                IspisiPoziciju(x, y, orijentacija);
            }
        }
        doslo_do_greske = false;
        std::cout << std::endl << "Unesi komandu: ";
        if(UnosKomande(komanda, parametar, kod_greske)) {
            IzvrsiKomandu(komanda, parametar, x, y, orijentacija);
        } else {
            PrijaviGresku(kod_greske);
            doslo_do_greske = true;
        }
    }
    std::cout << "Dovidjenja!";
	return 0;
}

void Idi(int &x, int &y, Pravci orijentacija, int korak) {
    // Postavljanje * tamo gdje se nalazimo jer idemo dalje
    // jer je pocetna koordinata matrice koju smo izabrali ustvari 10-y i 30+x
    grid.at(10-y).at(30+x) = '*';
    // radi_s_y => 0 - y se ne mijenja; 1 - y se povecava; -1 - y se smanjuje
    int radi_s_y{0}, radi_s_x{0}; // analagono i za radi_s_x
    
    // pozitivni dijelovi y ose => y se povecava
    if(orijentacija == Pravci::Sjever || orijentacija == Pravci::Sjeverozapad || orijentacija == Pravci::Sjeveroistok) {
        radi_s_y = 1;
    } 
    if(orijentacija == Pravci::Jug || orijentacija == Pravci::Jugozapad || orijentacija == Pravci::Jugoistok) {
        radi_s_y = -1;
    }
    if(orijentacija == Pravci::Istok || orijentacija == Pravci::Jugoistok || orijentacija == Pravci::Sjeveroistok) {
        radi_s_x = 1;
    } 
    if(orijentacija == Pravci::Zapad || orijentacija == Pravci::Sjeverozapad || orijentacija == Pravci::Jugozapad) {
        radi_s_x = -1;
    }

    int korak_je_poz_y{}, korak_je_poz_x{};
    // 1 i -1 ne predstavljaju true/false, nego se koriste za sabiranje/oduzimanje od osa
    // ako je korak>0 i y treba povecati ILI ako je korak<0 a y treba smanjiti
    if(radi_s_y != 0) {
        korak_je_poz_y = (((korak > 0 && radi_s_y == 1) || (korak < 0 && radi_s_y == -1)) ? 1 : -1);// 1 y se povecava -1 se smanjuje
    }
    if(radi_s_x != 0) {
        korak_je_poz_x = ((korak > 0 && radi_s_x == 1) || (korak < 0 && radi_s_x == -1) ? 1 : -1);
    }
    if(korak != 0) {
        // korak moze biti negativan
        for(int i=0; i<std::fabs(korak); i++) {
            y += korak_je_poz_y;
            x += korak_je_poz_x;
            // resetovanje koordinata u slucaju da dodje do prekoracenja okvira tj grid-a
            if(y > 10) {
                y = -10;
            }
            if(y < -10) {
                y = 10;
            }
            if(x > 30) {
                x = -30;
            }
            if(x < -30) {
                x = 30;
            }
            if(vidljivost) {
                grid.at(10-y).at(30+x) = '*';
            } 
        }
    }
    // jer je pocetna koordinata matrice koju smo izabrali ustvari 10-y i 30+x
    grid.at(10-y).at(30+x) = 'O';
}

void Rotiraj(Pravci &orijentacija, int ugao) {
    int rotacija = static_cast<int>(std::fabs(ugao)) % 8;
    while(rotacija > 0) {
        if(ugao < 0) {
            if(orijentacija == Pravci::Sjeverozapad) {
                orijentacija = Pravci::Sjever;
            } else {
                orijentacija = Pravci(static_cast<int>(orijentacija) + 1);
            }
        } else {
            if(orijentacija == Pravci::Sjever) {
                orijentacija = Pravci::Sjeverozapad;
            } else {
                orijentacija = Pravci(static_cast<int>(orijentacija) - 1);
            }
        }
        rotacija--;
    } 
}

void PostaviVidljivost(bool vidljiv) {
    vidljivost = vidljiv;
}

void IspisiPoziciju(int x, int y, Pravci orijentacija) {
    std::cout << "\nRobot je " << (vidljivost ? "vidljiv" : "nevidljiv") << ", nalazi se na poziciji (" << x << "," << y 
    << ") i gleda na ";
    switch(orijentacija) {
        case Pravci::Sjever:
            std::cout << "sjever";
            break;
        case Pravci::Jug:
            std::cout << "jug";
            break;
        case Pravci::Istok:
            std::cout << "istok";
            break;
        case Pravci::Zapad:
            std::cout << "zapad";
            break;
        case Pravci::Sjeverozapad:
            std::cout << "sjeverozapad";
            break;
        case Pravci::Sjeveroistok:
            std::cout << "sjeveroistok";
            break;
        case Pravci::Jugoistok:
            std::cout << "jugoistok";
            break;
        case Pravci::Jugozapad:
            std::cout << "jugozapad";
            break;
    }
    std::cout << ".";
}

void PrikaziTeren() {
    std::cout << std::endl << (std::string(63, '#')) << std::endl;
    for(int i=0; i<grid.size(); i++) {
        for(int j=0; j<grid.at(i).size(); j++) {
            if(j == 0 ) {
                std::cout << "#";
            }
            if(grid.at(i).at(j) != '*' && grid.at(i).at(j) != 'O') {
                std::cout << " ";
            } else {
                std::cout << grid.at(i).at(j);
            }
            if(j == grid.at(i).size()-1) {
                std::cout << "#";
            }
        }
        std::cout << std::endl;
    }
    std::cout << (std::string(63, '#'));
}

void PrijaviGresku(KodoviGresaka kod_greske) {
    switch(kod_greske) {
        case KodoviGresaka::PogresnaKomanda:
            std::cout << "\nNerazumljiva komanda!";
            break;
        case KodoviGresaka::NedostajeParametar:
            std::cout << "\nKomanda trazi parametar koji nije naveden!";
            break;
        case KodoviGresaka::SuvisanParametar:
            std::cout << "\nZadan je suvisan parametar nakon komande!";
            break;
        case KodoviGresaka::NeispravanParametar:
            std::cout << "\nParametar komande nije ispravan!";
            break;
    }
}

void IzvrsiKomandu(Komande komanda, int parametar, int &x, int &y, Pravci &orijentacija) {
    switch(komanda) {
        case Komande::Idi:
            Idi(x, y, orijentacija, parametar);
            break;
        case Komande::Rotiraj:
            Rotiraj(orijentacija, parametar);
            break;
        case Komande::Sakrij:
            PostaviVidljivost(false);
            break;
        case Komande::PrikaziTeren:
            PrikaziTeren();
            break;
        case Komande::Otkrij:
            PostaviVidljivost(true);
            break;
        default:
            break;
    }
}

// spisak dozvoljenih komandi {Idi, Rotiraj, Sakrij, Otkrij, PrikaziTeren, Kraj};
bool UnosKomande(Komande &komanda, int &parametar, KodoviGresaka &kod_greske) {
    char znak1;
    std::cin >> znak1;
    switch (znak1) {
        case 'I':
            komanda = Komande::Idi;
            break;
        case 'R':
            komanda = Komande::Rotiraj;
            break;
        case 'S':
            break;
        case 'T':
            while(std::cin.peek() == ' ' || std::cin.peek() == '\t') std::cin.get();
            if(std::cin.peek() != '\n') {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                kod_greske = KodoviGresaka::SuvisanParametar;
                return false;
            }
            komanda = Komande::PrikaziTeren;
            return true;
        case 'K':
            while(std::cin.peek() == ' ' || std::cin.peek() == '\t') std::cin.get();
            if(std::cin.peek() != '\n') {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                kod_greske = KodoviGresaka::SuvisanParametar;
                return false;
            }
            komanda = Komande::Kraj;
            return true;
        default:
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            kod_greske = KodoviGresaka::PogresnaKomanda;
            return false;
    }
    if(znak1 == 'I' || znak1 == 'R') {
        char sljedeci;
        while((sljedeci = std::cin.peek()), sljedeci == '\t' || sljedeci == ' ') std::cin.get();
        if(std::cin.peek() == '\n') {
            std::cin.ignore(1000, '\n');
            kod_greske = KodoviGresaka::NedostajeParametar;
            return false;
        }
        double znak2;
        if(!(std::cin >> znak2)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            kod_greske = KodoviGresaka::NeispravanParametar;
            return false;
        } else if(znak2 == static_cast<int>(znak2)) {
            parametar = znak2;
            if(std::cin.peek() != ' ' && std::cin.peek() != '\t' && std::cin.peek() != '\n') {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                kod_greske = KodoviGresaka::NeispravanParametar;
                return false;
            }
            char sljedeci;
            while((sljedeci = std::cin.peek()), (sljedeci == '\t' || sljedeci == ' ')) {
                //std::cin.ignore(1, '\n');
                std::cin.get();
            }
            if(sljedeci != '\n') {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                kod_greske = KodoviGresaka::SuvisanParametar;
                return false;
            }
            return true;
        }
    }
    // Funkcija za testiranje da li ima suvisnih parametara, plus signalizira da li je + ili - drugi    
    // parametar koji trazimo
    auto p = [](Komande &komanda, KodoviGresaka &kod_greske, bool plus, bool &postavljanje_greske) -> bool {
        char sljedeci;
        while((sljedeci = std::cin.peek()), (sljedeci == '\t' || sljedeci == ' ')) {
            //std::cin.ignore(1, '\n');
            std::cin.get(); // bolje vjerovatno
        }
        
        // vec smo procitali da li je + ili - stoga ako nisu sljedece praznine => Suvisan
        if(std::cin.peek() != '\n') {
            std::cin.ignore(1000, '\n');
            kod_greske = KodoviGresaka::SuvisanParametar;
            postavljanje_greske = true;
            return false;
        }
        // ako su sve praznine onda trazimo komandu
        // if(plus) {
        //     //komanda = Komande::Sakrij;
        // } else {
        //     komanda = Komande::Otkrij;
        // }
        return true;
    };
    if(znak1 == 'S') {
        // cin podrazumijevano ignorira bjeline pa nema problema ako je S\t' '\n
        // gledamo da li je samo uneseno slovo S
        while(std::cin.peek() == ' ' || std::cin.peek() == '\t') std::cin.get();
        if(std::cin.peek() == '\n') {
            kod_greske = KodoviGresaka::NedostajeParametar;
            return false;
        }
        char znak2;
        bool kodGreske_je_postavljen = false;
        std::cin >> znak2;
        if(znak2 == '+' && p(komanda, kod_greske, true, kodGreske_je_postavljen)) {
            komanda = Komande::Sakrij;
        } else if(znak2 == '-' && p(komanda, kod_greske, false, kodGreske_je_postavljen)) {
            komanda = Komande::Otkrij;
        } else if(kod_greske == KodoviGresaka::SuvisanParametar && kodGreske_je_postavljen) {
            //std::cin.ignore(1000, '\n');
            kod_greske = KodoviGresaka::SuvisanParametar;
            return false;
        } else {
            std::cin.ignore(1000, '\n');
            kod_greske = KodoviGresaka::PogresnaKomanda;
            return false;
        }
    }
    return true;
}