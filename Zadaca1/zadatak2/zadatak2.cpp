// Autor: Husić Muhamed
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <iomanip>

typedef std::vector<std::vector<double>> MATRICA;

//N je red filtriranja
MATRICA UsrednjavajuciFilter(MATRICA zaFiltriranje, int N){
    if(N < 0) {
        throw std::domain_error("Neispravan red filtriranja");
    }
    std::vector<std::vector<double>> filtrirana_matrica(zaFiltriranje.size());
    for(int i=0; i<zaFiltriranje.size(); i++) {
        for(int j=0; j<zaFiltriranje.at(i).size(); j++) {
            
            int prvi_red{i}, prva_kolona{j}, brojac_reda{0}, brojac_kolone{0}; //brojaci broje koliko smo elemenata preskocili
            while( prvi_red-N < 0 ) {
                prvi_red++;
                brojac_reda++;
            }
            while(prva_kolona-N < 0) {
                prva_kolona++;
                brojac_kolone++;
            }
            // -----------------Donji elementi----------------
            int zadnji_red{i}, zadnja_kolona{j}; //krecemo od ovih elemenata
            while( zadnji_red+N >= zaFiltriranje.size() ) {
                zadnji_red--;
                brojac_reda++;
            }
           
            // while( zadnja_kolona+N >= zaFiltriranje.at(zadnji_red).size() ) {
            //     zadnja_kolona--;
            //     brojac_kolone++;
            // }
            prvi_red -= N;
            prva_kolona -= N;
            zadnji_red += N;
            double suma{0};
            // -----------------------------------------------------------------------
            int dijeli_sa{0}; //jer sam zaboravio da se rubovi dijele s drugim br;
            for(int k=prvi_red; k <= zadnji_red; k++) { //!!!!!!!!!!!!!!!!!!!!!PRVI-ZADNJI < ili <=
                int uzeti_elementi{0}; //0 elemenata smjesteni u sumu za filtriranje
                int potrebni_elementi = 2 * N + 1 - brojac_kolone;
                for(int m=prva_kolona; m < zaFiltriranje.at(k).size(); m++) {
                    // std::cout << "k: " << k << ",   m: " << m << "---> pot_elem-prv_kol: "<< "\n";
                    if(uzeti_elementi >= potrebni_elementi) {
                        break;
                    }
                    uzeti_elementi++;
                    dijeli_sa++;
                    // std::cout << zaFiltriranje.at(k).at(m) << "\t";
                    suma += zaFiltriranje.at(k).at(m);
                }
            }
            // std::cout << std::endl << "\t----------suma: " << suma << "  --------------dijeli sa: " << dijeli_sa << std::endl;
            filtrirana_matrica.at(i).push_back(suma / dijeli_sa);
        }
    }
    return filtrirana_matrica;
}

int main () {
    std::cout << "Unesite broj redova i kolona matrice: ";
    int br_redova{0}, br_kolona{0};
    std::cin >> br_redova >> br_kolona;
    std::cout << "Unesite elemente matrice: " << std::endl;
    MATRICA za_filtriranje(br_redova, std::vector<double>(br_kolona));
    for(int i=0; i<br_redova; i++) {
        for(int j=0; j<br_kolona; j++) {
            std::cin >> za_filtriranje.at(i).at(j);
        }
    }
    std::cout << "Unesite red filtriranja: ";
    int red_filtriranja{0};
    std::cin >> red_filtriranja;
    try {
        za_filtriranje = UsrednjavajuciFilter(za_filtriranje, red_filtriranja);
        std::cout << "Matrica nakon filtriranja:" << std::endl;
        for(std::vector<double> red : za_filtriranje) {
            for(double x : red) {
                std::cout << std::fixed << std::setprecision(2) << std::setw(7) << x;
            }
            std::cout << std::endl;
        }
    } catch(std::domain_error e) {
        std::cout << "GRESKA: Neispravan red filtriranja!" << std::endl;
    }
	return 0;
}
