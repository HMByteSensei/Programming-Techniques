#include <iostream>
#include <cmath>
#include <iomanip>
//#include <exeptional>

struct Vrijeme {
    int sati, minute, sekunde;
};

void TestirajVrijeme(const Vrijeme &v) {
    if(v.sati < 0 || v.sati > 23 || v.minute < 0 || v.minute > 59 || v.sekunde < 0 || v.sekunde > 59) {
        throw std::domain_error("Neispravno vrijeme");
    }
}
void IspisiVrijeme(const Vrijeme &v) {
    TestirajVrijeme(v);
    std::cout << std::setfill('0') << std::setw(2) << v.sati << ":" << std::setw(2) << v.minute << ":"
    << std::setw(2) << v.sekunde;
}

Vrijeme SaberiVrijeme(Vrijeme &v1, Vrijeme &v2) {
    int v1_sekunde = v1.sekunde + v1.minute * 60 + v1.sati * 3600;
    int v2_sekunde = v2.sekunde + v2.minute * 60 + v2.sati * 3600;
    TestirajVrijeme(v1);
    TestirajVrijeme(v2);
    int ostatak = v1_sekunde + v2_sekunde;
    return {ostatak / 3600 % 24, ostatak % 3600 / 60, ostatak % 60};
}

void Unesi(Vrijeme &v1) {
    std::cin >> v1.sati >> v1.minute >> v1.sekunde;
    TestirajVrijeme(v1);
}
int main () {
    Vrijeme v1, v2;
    try {
        std::cout << "Unesite prvo vrijeme (h m s): ";
        Unesi(v1);
        std::cout << "Unesite drugo vrijeme (h m s): ";
        Unesi(v2);
        std::cout << "Prvo vrijeme: ";
        IspisiVrijeme(v1);
        std::cout << "\nDrugo vrijeme: ";
        IspisiVrijeme(v2);
        std::cout << "\nZbir vremena: ";
        IspisiVrijeme(SaberiVrijeme(v1, v2));
    } catch(std::domain_error e) {
        std::cout << e.what();
    }
	return 0;
}
