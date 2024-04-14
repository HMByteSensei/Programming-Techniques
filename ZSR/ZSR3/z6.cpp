#include <iostream>

bool Pitagora(double kateta1, double kateta2, double hipotenuza) {
    const double epsilon = 0.0000001;
    return (((kateta1 * kateta1 + kateta2 * kateta2) - hipotenuza * hipotenuza) < epsilon) ? true : false;
}

int main() {
    std::cout << "Unesite stranice trougla: ";
    double a, b, c;
    std::cin >> a;
    if(!(std::cin)) std::exit(0);
    
    std::cin >> b;
    if(!std::cin) std::exit(0);

    std::cin >> c;
    if(!std::cin) std::exit(0);

    if(c >= a && c >= b) {
        //std::cout << "U c-u smo   " << ((a*a + b*b))<< "  =  " << c*c << std::endl;
        if(Pitagora(a, b, c)) std::cout << "Ovi brojevi cine stranice pravouglog trougla." << std::endl;
    }
    else if(a >= b && a >= c) {
        if(Pitagora(c, b, a)) std::cout << "Ovi brojevi cine stranice pravouglog trougla." << std::endl;
    }
    else if(b >= a && b >= c) {
        if(Pitagora(a, c, b)) std::cout << "Ovi brojevi cine stranice pravouglog trougla." << std::endl;
    }
    else std::cout << "Ovi brojevi ne cine stranice pravouglog trougla." << std::endl;

    return 0;
}  