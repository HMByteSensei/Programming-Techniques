#include <iostream>
#include <vector>

bool SviElementiSuJednaki(std::vector<double> v) {
    for(int i=0; i<v.size(); i++) {
        for(int j=(i+1); j<v.size(); j++)
            if(v.at(i) != v.at(j)) {
                return false;
            }    
    }
    return true;
}

bool SviElementiSuRazliciti(std::vector<double> v) {
    for(int i=0; i<v.size(); i++) {
        for(int j=(i+1); j<v.size(); j++)
            if(v.at(i) == v.at(j)) {
                return false;
            }
    }
    return true;
}

int main() {
    std::cout << "Unesite broj elemenata n: ";
    int n;
    std::cin >> n; //predpostavljamo da je unesen prirodan cijeli broj
    std::vector<double> v(n);
    int element{0};
    int brojac{0};
    do {
        std::cin >> element;
        if(std::cin.fail()) {
            std::cout << "Pogresan unos!" << std::endl;
            std::cin.clear();
            std::cin.ignore();
        }
        v.at(brojac) = element;
        brojac++;
    }while(element != 0 && brojac<n);
    
    // for(int x : v) std::cout << x << "\t";
    std::cout << "Svi elementi su jednaki? " << SviElementiSuJednaki(v)
    << std::endl << "Svi elementi su razliciti? " << SviElementiSuRazliciti(v) << std::endl;
    return 0;
}