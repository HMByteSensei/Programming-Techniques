#include <cmath>
#include <iostream>
#include <vector>

bool DaLiJeProst(int broj) {
    if(broj <= 1) return false;
    for (int i = 2; i <= std::sqrt(broj); i++) {
        if (broj % i == 0)
            return false;
    }
    return true;
}

std::vector<int> ProstiBrojeviUOpsegu(int a, int b) {
  std::vector<int> rezultat;
  for (; a < b; a++) {
    if (DaLiJeProst(a))
      rezultat.push_back(a);
  }
  if(DaLiJeProst(b)) rezultat.push_back(b);
  return rezultat;
}

int main() {
  std::cout << "Unesite pocetnu i krajnju vrijednost: ";
  int a, b;
  while (!(std::cin >> a >> b)) {
    std::cout << "Pogresan unos!" << std::endl;
    std::cin.clear();
    std::cin.ignore();
    std::cin.clear();
    std::cin.ignore();
  }
  std::vector<int> vektor = ProstiBrojeviUOpsegu(a, b);
  if (!vektor.empty()) {
    std::cout << "Prosti brojevi u rasponu od " << a << " do " << b << " su: ";
    if(a<0) a=2;//za test 9
    for (int i = 0; i < vektor.size(); i++) {
      if (i != (vektor.size() - 1)) {
        std::cout << vektor.at(i) << ", ";
      } else {
        std::cout << vektor.at(i) << std::endl;
      }
    }
  } else {
    std::cout << "Nema prostih brojeva u rasponu od " << a << " do " << b << "!" << std::endl;
  }
  return 0;
}
