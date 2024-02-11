#include <deque>
#include <iostream>

int pronadi_medijan(std::deque<int> dek) {
    for (int i : dek) {
        int manji = 0;
        int veci = 0;
        for (int j : dek) {
            if (j < i) {
                manji += 1;
            } else if (j > i) {
                veci += 1;
            }
        }
        if (manji == veci) {
            return i;
        }
    }
}

int main() {
    std::cout << "Unesite n: ";
    int n;
    std::cin >> n;
    std::deque<int> dek(n);
    for(int i=0; i<n; i++) {
        while(!(std::cin >> dek.at(i))){
            std::cout << "Pogresan unos!\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
    }
    int rezultat = pronadi_medijan(dek);
    //for(int i=0; i<dek.size(); i++) {
        std::cout << "Medijan je " << pronadi_medijan(dek) << "\n";
    //}
    std::cout << std::endl;
    return 0;
}