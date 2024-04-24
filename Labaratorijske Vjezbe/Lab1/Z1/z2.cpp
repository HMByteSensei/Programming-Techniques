// TP 2016/2017: Tutorijal 1, Zadatak 2
#include <algorithm>
#include <cmath>
#include <iostream>

int main() {
  std::cout << "Unesite tri broja: ";
  double a, b, c;
  std::cin >> a >> b >> c;
  // Teorem o nejednakosti trougla
  if (!((a + b > c) && (a + c > b) && (b + c > a))) {
    std::cout << "Ne postoji trougao cije su duzine stranica " << a << ", " << b
              << " i " << c << "!" << std::endl;
  } else {
    std::cout << "Obim trougla sa duzinama stranica " << a << ", " << b << " i "
              << c << " iznosi " << a + b + c << "." << std::endl;
    double s = (a + b + c) / 2;
    std::cout << "Njegova povrsina iznosi "
              << std::sqrt(s * (s - a) * (s - b) * (s - c)) << "." << std::endl;

    double najmanja_stranica = std::min({a, b, c});
    double najveca_stranica = std::max({a, b, c});
    double treca_stranica = (a + b + c) - najmanja_stranica - najveca_stranica;

    const double pi = 4 * atan(1);
    double ugao = std::acos((std::pow(najveca_stranica, 2) + std::pow(treca_stranica, 2) - std::pow(najmanja_stranica, 2)) / (2 * treca_stranica * najveca_stranica));

    double minute=((ugao * 180 / pi) - static_cast<int>(ugao * 180 / pi)) * 60;
    double sekunde = (minute - static_cast<int>(minute)) * 60;

    //std::cout << ugao << std::endl;
    std::cout << "Njegov najmanji ugao ima "
              << static_cast<int>(ugao * 180 / pi) << " stepeni, "
              << static_cast<int>(minute) << " minuta i "
              << static_cast<int>(sekunde) << " sekundi." << std::endl;
  }
  return 0;
}