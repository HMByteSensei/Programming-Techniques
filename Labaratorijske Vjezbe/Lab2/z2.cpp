#include <cmath>
#include <iostream>
#include <vector>

bool TestPerioda(std::vector<double> vektor, int period) {
  if(period >= vektor.size() || period == 0) return false;
  for (int i = 0; i < vektor.size() - period; i++) {
    if (vektor.at(i) != vektor.at(i + period))
      return false;
  }
  return true;
}

int OdrediOsnovniPeriod(std::vector<double> vektor) {
  for (int i = 0; i < vektor.size(); i++) {
    for (int j = (i + 1); j < vektor.size(); j++) {
      if (vektor.at(i) == vektor.at(j)) {
        if (TestPerioda(vektor, j)) {
          return j;
        }
      }
    }
  }
  return 0;
}

int main() {
  std::cout << "Unesite slijed brojeva (0 za kraj): ";
  std::vector<double> vektor;
  do {
    double element;
    std::cin >> element;
    if (element == 0)
      break;
    vektor.push_back(element);
  } while (true);
  if (OdrediOsnovniPeriod(vektor))
    std::cout << "Slijed je periodican sa osnovnim periodom "
              << OdrediOsnovniPeriod(vektor) << "." << std::endl;
  else
    std::cout << "Slijed nije periodican!" << std::endl;
  return 0;
}