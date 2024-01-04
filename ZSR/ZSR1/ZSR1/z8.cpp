#include <iostream>

int main() {
    int br1, br2, br3, br4, br5, br6;
    std::cout << "Unesite 6 brojeva: ";
    std::cin >> br1 >> br2 >> br3 >> br4 >> br5 >> br6;
    if(!std::cin) {    //zasto ako unesemo br2 odmah provjerava ovo i prekida s radom ako nije br
        std::cout << "Treba broj"; 
        std::exit(0);
    }
    if (br1 > 0 && br2 > 0 && br3 > 0 && br4 > 0 && br5 > 0 && br6 > 0) {
        std::cout << "Svi brojevi su pozitivni." << std::endl;
    }
    else std::cout << "Nisu svi brojevi pozitivni." << std::endl;

    if(!(br1 % 2) && !(br2 % 2) && !(br3 % 2) && !(br4 % 2)  && !(br5 % 2) && !(br6 % 2)) {
        std::cout << "Svi su parni." << std::endl;
    }
    else std::cout << "Nisu svi brojevi parni." << std::endl;

    return 0;
}