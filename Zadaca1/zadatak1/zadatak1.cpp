/*
 * Autor: Husić Muhamed
*/
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <array>
#include <climits>

enum class TretmanNegativnih {IgnorirajZnak, Odbaci, PrijaviGresku};

int MultiplikativniDigitalniKorijen(long long int brojCijiSeMDKtrazi, int baza) {
    //U slucaju da je brojCijiSeMDKtrazi negativan, njegov znak se prosto treba ignorirati
    // std::cout << "\t" << brojCijiSeMDKtrazi << "\n";
    if(brojCijiSeMDKtrazi < 0) {
        brojCijiSeMDKtrazi = -brojCijiSeMDKtrazi;
    }
    //ako je baza neispravna
    if(baza < 2) {
        throw std::domain_error("Neispravna baza");    //!!!!!!!!Bacanje izuzetka!!!!!!!!
    }
    
    //MDK bilo kojeg broja mora biti od 0 do baza-1
    while(brojCijiSeMDKtrazi > (baza - 1)) {
        long long int pretvoren{1};
        while(brojCijiSeMDKtrazi != 0) {
            int ostatak = brojCijiSeMDKtrazi% baza;
            brojCijiSeMDKtrazi /= baza;
            pretvoren *= ostatak;
        }
        brojCijiSeMDKtrazi = pretvoren;
    }
    return brojCijiSeMDKtrazi;
}

std::array<std::vector<int>, 10> RazvrstajBrojeve(std::vector<long long int> za_razvrstavanje,TretmanNegativnih tretman) {
    std::array<std::vector<int>, 10> rank_matrica;
    int baza{10};
    if(tretman == TretmanNegativnih::IgnorirajZnak) {
        for(long long int x : za_razvrstavanje) {
            if(x<0) x = (-x);
            long long int rank = MultiplikativniDigitalniKorijen(x, baza);
            //indeksi rank_matrice 0-9 => rank odgovara indeksu
            if(rank <= (baza-1)) {
                rank_matrica.at(rank).push_back(x);
            }
        }
    } else if(tretman == TretmanNegativnih::Odbaci) {
        for(long long int x : za_razvrstavanje) {
            //negativni elementi se ignoriraju/odbacuju
            if(x < 0) continue;
            long long int rank{MultiplikativniDigitalniKorijen(x, baza)};
            if(rank < (baza-1)) {
                rank_matrica.at(rank).push_back(x);
            }
        }
    } else {// if(tretman == TretmanNegativnih::PrijaviGresku) {
        for(long long int x : za_razvrstavanje) {
            if(x<0) {
                throw std::domain_error("Nije predvidjeno razvrstavanje negativnih brojeva");//!!Bacanje Izuzetka!!
            }
            long long int rank = MultiplikativniDigitalniKorijen(x, baza);
            //indeksi rank_matrice 0-9 => rank odgovara indeksu
            if(rank <= (baza-1)) {
                rank_matrica.at(rank).push_back(x);
            }
        }
     } // else {
    //     throw std::invalid_argument("Unesen je pogresan argument!"); //!!!!Bacanje izuzetka!!!!!
    // }
    return rank_matrica;
}

int main() {
    std::cout << "Unesite brojeve (bilo koji ne-broj oznacava kraj): ";
    int element;
    std::vector<long long int> unos_vektor;
    while(std::cin >> element) {
        unos_vektor.push_back(element);
    }
    try {
        std::array<std::vector<int>, 10> razvrstano = RazvrstajBrojeve(unos_vektor, TretmanNegativnih::PrijaviGresku);
        std::cout << std::endl << "Rezultati razvrstavanja po multiplikativnom digitalnom korijenu:" 
        << std::endl;
        for(int i=0; i<10; i++) {
            if(!razvrstano.at(i).empty()) {
                std::cout << i << ": ";
                for(int j=0; j<razvrstano.at(i).size(); j++) {
                    std::cout << razvrstano.at(i).at(j) << " ";
                }
                std::cout << std::endl;
            }
        }
    } catch (std::domain_error e) {
        std::cout << "\nNije podrzano razvrstavanje negativnih brojeva!" << std::endl;
    }
    return 0;
}