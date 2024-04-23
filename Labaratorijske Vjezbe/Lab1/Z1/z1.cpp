#include <cmath>
#include <iostream>

int main() {
  int duzina, sirina, visina;
  std::cout << "Unesite duzinu, sirinu i dubinu bazena u metrima: ";
  std::cin >> duzina >> sirina >> visina; //[m]

  std::cout << "Unesite sirinu plocice u centimetrima: ";
  int sirina_plocice;
  std::cin >> sirina_plocice; //[cm]

  int duzina_cm = duzina * 100;
  int sirina_cm = sirina * 100;
  int visina_cm = visina * 100;
  if ((duzina_cm % sirina_plocice == 0) && (sirina_cm % sirina_plocice == 0) &&
      (visina_cm % sirina_plocice == 0)) {
    std::cout << std::endl
              << "Za poplocavanje bazena dimenzija " << duzina << "x" << sirina
              << "x" << visina << "m sa plocicama dimenzija " << sirina_plocice
              << "x" << sirina_plocice << "cm potrebno je "
              << (duzina_cm * sirina_cm + 2 * duzina_cm * visina_cm +
                  2 * sirina_cm * visina_cm) /
                     (sirina_plocice * sirina_plocice)
              << " plocica." << std::endl;
  } else {
    std::cout << std::endl
              << "Poplocavanje bazena dimenzija " << duzina << "x" << sirina
              << "x" << visina << "m sa plocicama dimenzija " << sirina_plocice
              << "x" << sirina_plocice
              << "cm\n nije izvodljivo bez lomljenja plocica!" << std::endl;
  }
  return 0;
}