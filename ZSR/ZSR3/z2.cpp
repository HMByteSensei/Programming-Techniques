#include <iostream>

int main() {
    std::cout << "Unesite brzinu broda u cvorovima: ";
    int vel_cvorova; //velocity cvorova
    while(!(std::cin >> vel_cvorova)) {
        std::cout << "Potrebno je samo da unesete broj za datu brzinu." << std::endl;
        std::cin.clear();
        std::cin.ignore(1000, '\n');
    }
    const int morska_milja = 1852; //metara

    std::cout << vel_cvorova << " je jednaka " << (vel_cvorova * morska_milja/1000.) 
    << "[km/h]." << std::endl;
    return 0;
}