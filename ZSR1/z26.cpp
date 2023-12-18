#include <iostream>

int main() {
    double realan_x;
    int stepen_N;

    while(!(std::cin >> realan_x >> stepen_N)) {
        std::cout << "Pogresan unos!" << std::endl;
        if(std::cin.fail()) {
            std::cin.ignore(1000, '\n');
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cin.clear();
        }
    }

    double a_N{0}; //jednoobrazna inicijalizacija
    double kopija{realan_x}, P{0};
    for(int i=0; i<stepen_N; i++) {
        std::cin >> a_N;
        if(std::cin.fail()) {
            std::cout << "Pogresan unos!" << std::endl;
            std::cin.ignore(1000, '\n');
            std::cin.clear();
            i--;
        }
        if(i != 0 && i!=1) { realan_x = realan_x * kopija; }
        if(i==0) { P+= a_N; }
        else { P += a_N/realan_x; }//pravo P ce biti: P = P*realan_x, buduci da smo izvukli realan_x^n
        //std::cout << "\t" << P;
    }
    std::cout << "Trazena vrijednost iznosi: " << P*realan_x << std::endl;
    return 0;
}