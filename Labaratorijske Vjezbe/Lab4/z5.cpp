#include <iostream>
#include <cmath>
#include <vector>

template <typename Tip>
std::vector<Tip> Presjek(const std::vector<Tip> &v1, const std::vector<Tip> &v2) {
    std::vector<Tip> rezultat;
    for(int i=0; i<v1.size(); i++) {
        for(auto x : v2) {
            if(x == v1.at(i)) {
                bool vec_postoji{false};
                for(int k=0; k<rezultat.size(); k++) {
                    if(x == rezultat.at(k)) {
                        vec_postoji = true;
                        break;
                    }
                }
                if(!vec_postoji) {
                    rezultat.push_back(x);
                    break;
                }
            }
        }
    }
    return rezultat;
}

int main ()
{
    std::cout << "Test za realne brojeve..." << std::endl;
    std::cout << "Unesite broj elemenata prvog vektora: ";
    int broj_elemenata;
    std::cin >> broj_elemenata;
    std::cout << "Unesite elemente prvog vektora: ";
    std::vector<double> v1, v2;
    for(int i=0; i<broj_elemenata; i++) {
        double element;
        std::cin >> element;
        v1.push_back(element);
    }
    std::cout << "Unesite broj elemenata drugog vektora: ";
    std::cin >> broj_elemenata;
    // Autor: Muhamed Husic
    std::cout << "Unesite elemente drugog vektora: ";
    for(int i=0; i<broj_elemenata; i++) {
        double element;
        std::cin >> element;
        v2.push_back(element);
    }
    std::cout << "Zajednicki elementi su:";
    std::vector<double> rezultat = Presjek(v1, v2);
    for(double x : rezultat) {
        std::cout << " " << x;
    }
    std::cout << "\nTest za stringove...\n";
    std::cout << "Unesite broj elemenata prvog vektora: ";
    std::cin >> broj_elemenata;
    std::cin.ignore(1000, '\n');
    std::cout << "Unesite elemente prvog vektora (ENTER nakon svakog unosa): ";
    std::vector<std::string> s1, s2;
    for(int i=0; i<broj_elemenata; i++) {
        std::string element;
        std::getline(std::cin, element);
        //std::cin.ignore(1000, '\n');
        s1.push_back(element);
    }
    
    std::cout << "Unesite broj elemenata drugog vektora: ";
    std::cin >> broj_elemenata;
    std::cin.ignore(1000, '\n');
    std::cout << "Unesite elemente drugog vektora (ENTER nakon svakog unosa): ";
    for(int i=0; i<broj_elemenata; i++) {
        std::string element;
        std::getline(std::cin, element);
        // std::cin >> std::ws;
        // std::cin.ignore(1000, '\n');
        s2.push_back(element);
    }
    std::cout << "\nZajednicki elementi su:";
    std::vector<std::string> sa_stringovima = Presjek(s1, s2);
    for(std::string x : sa_stringovima) {
        std::cout << " " << x;
    }
	return 0;
}
