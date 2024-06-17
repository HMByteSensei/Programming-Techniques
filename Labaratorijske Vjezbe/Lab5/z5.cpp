#include <iostream>
#include <cmath>
#include <iomanip>

double TrapeznoPravilo(double f(double), double a, double b, int n) {
    double rezultat{(b-a) / n};
    double suma{1./2 * f(a) + 1./2 * f(b)};
    for(int i=1; i<=n-1; i++) {
        suma += f(a + (b-a)/n * i);
    }
    return rezultat * suma;
}

int main () {
    std::cout << "Unesite broj podintervala: ";
    int n;
    std::cin >> n;
    std::cout << "Za taj broj podintervala priblizne vrijednosti integrala iznose: " << std::endl;
    const double pi = atan(1) * 4;
    std::cout << "- Za funkciju sin x na intervalu (0,pi): " << std::fixed 
    << std::setprecision(5) << TrapeznoPravilo(std::sin, 0, pi, n) << std::endl;
	std::cout << "- Za funkciju x^3 na intervalu (0,10): " << std::fixed << std::setprecision(2)
    << TrapeznoPravilo([](double x){return x*x*x;}, 0, 10, n) << std::endl;
    std::cout << "- Za funkciju 1/x na intervalu (1,2): " << std::fixed << std::setprecision(5) 
    << TrapeznoPravilo([](double x) -> double { return 1/x; }, 1, 2, n) << std::endl;
    return 0;
}