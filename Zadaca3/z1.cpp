#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <functional>
#include <algorithm>

std::function<double(double)> LagrangeovaInterpolacija(std::vector<std::pair<double, double>> uredeni_parovi) {
    for(int i = 0; i < uredeni_parovi.size(); i++) {
        for(int j = i + 1; j < uredeni_parovi.size(); j++) {
            if(uredeni_parovi.at(i).first == uredeni_parovi.at(j).first) {
                throw std::domain_error("Neispravni cvorovi");
            }
        }
    }
    return [uredeni_parovi] (double x) {
        double suma{0};
        // SPECIFICNA SITUACIJA DIJELJENJE S BESK.
        //if(uredeni_parovi.size() <= 1)  return 0.; // ako imamo samo jedan element proizvod se nece ni izvrsiti pa ce biti 0
        for(int i = 0; i < uredeni_parovi.size(); i++) {
            double proizvod = 1;
            for(int j = 0; j < uredeni_parovi.size(); j++) {
                if(j == i) continue;
                proizvod *= (x - uredeni_parovi.at(j).first) / (uredeni_parovi.at(i).first - uredeni_parovi.at(j).first);
            }
            suma += (uredeni_parovi.at(i).second * proizvod);
        }
        return suma;
    };
}

std::function<double(double)> LagrangeovaInterpolacija(std::function<double(double)> funkcija, double x_min, double x_max, double delta_x) {
    if(x_min > x_max || delta_x <= 0) {
        throw std::domain_error("Nekorektni parametri");
    }
    std::vector<std::pair<double, double>> uredeni_par;
    for(; x_min < x_max; x_min += delta_x) {
        uredeni_par.push_back({x_min, funkcija(x_min)});
    }
    const double epsilon = 1e-5;
    if(std::fmod((x_max - x_min), delta_x) < epsilon) {
        uredeni_par.push_back({x_max, funkcija(x_max)});
    }
    //std::cout << "\n" << uredeni_par.at(0).first << "\t" << uredeni_par.at(0).second<<"\n";
    return [uredeni_par] (double x) {
        double suma{0};
        // SPECIFICNA SITUACIJA DIJELJENJE S BESK.
        if(uredeni_par.size() < 1)  return 0.; // ako imamo manje od jednog elementa proizvod se nece ni izvrsiti pa ce biti 0
        for(int i = 0; i < uredeni_par.size(); i++) {
            double proizvod = 1;
            for(int j = 0; j < uredeni_par.size(); j++) {
                if(j == i) continue;
                proizvod *= (x - uredeni_par.at(j).first) / (uredeni_par.at(i).first - uredeni_par.at(j).first);
            }
            suma += (uredeni_par.at(i).second * proizvod);
        }
        return suma;
    };
}

int main() {
    std::cout << "Odaberite opciju (1 - unos cvorova, 2 - aproksimacija): ";
    int opcija;
    std::cin >> opcija;
    if(opcija == 1) 
    {
        std::cout << "Unesite broj cvorova: ";
        int broj_cvorova;
        std::cin >> broj_cvorova;
        std::cout << "Unesite cvorove kao parove x y: ";
        std::vector<std::pair<double, double>> uredeni_parovi;
        for(int i=0; i<broj_cvorova; i++) {
            std::pair<double, double> par;
            std::cin >> par.first >> par.second;
            uredeni_parovi.push_back(par);
        }
        try {
            auto P = LagrangeovaInterpolacija(uredeni_parovi);
            // trazimo min i max element koji se nalazi na kraju intervala, da bi bili u stanju ispitati
            // da li je dobijena vrijednost ekstrapolacija
            double x_min = (*std::min_element(uredeni_parovi.begin(), uredeni_parovi.end(), [](std::pair<double, double> x, std::pair<double, double> y) { return x.first < y.first; } )).first;
            double x_max = (*std::min_element(uredeni_parovi.begin(), uredeni_parovi.end(), [](std::pair<double, double> x, std::pair<double, double> y) { return x.first > y.first; } )).first;
            for(;;) {
                std::cout << "Unesite argument (ili \"kraj\" za kraj): ";
                double arg;
                if(!(std::cin >> arg)) {
                    return 0;
                }
                double izr_P_arg = P(arg);
                std::cout << "f(" << arg << ") = " << izr_P_arg << 
                ((izr_P_arg < x_min || izr_P_arg > x_max) ? " [ekstrapolacija]" : "") << std::endl;
            }
        } catch(std::domain_error e) {
            std::cout << e.what() << std::endl;
        }

    }
    else if(opcija == 2) 
    {
        std::cout << "Unesite krajeve intervala i korak: ";
        double x_min, x_max, delta_x;
        std::cin >> x_min >> x_max >> delta_x;
        try {
            auto f_x = [](double x) { return x*x + std::sin(x) + std::log(x+1); };
            auto P = LagrangeovaInterpolacija(f_x, x_min, x_max, delta_x);
            for(;;) {
                std::cout << "Unesite argument (ili \"kraj\" za kraj): ";
                double arg;
                if(!(std::cin >> arg)) {
                    return 0;
                }
                double izr_P_arg = P(arg);
                std::cout << "f(" << arg << ") = " << f_x(arg) << " P(" << arg << ") = " << izr_P_arg << 
                ((arg < x_min || arg > x_max) ? " [ekstrapolacija]" : "") << std::endl;
            }
        } catch(std::domain_error e) {
            std::cout << e.what() << std::endl;
        }
    }
    return 0;
}