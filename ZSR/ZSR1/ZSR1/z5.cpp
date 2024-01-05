#include <iostream>
#include <cmath>

int main() {
    std::cout << "Unesite koeficjente a, b i c kvadratne jednacine ax^2 + bx + c: ";
    int a, b, c;
    std::cin >> a;
    std::cin.ignore(1000, '\n');
    
    std::cin >> b;
    std::cin.ignore(1000, '\n');

    std::cin >> c;
    std::cin.ignore(1000, '\n');
    double determinanta = b * b - 4 * a * c;
    if( (a != 0) ) {
        if(determinanta > 0) {
            double x1;
            x1 = (-b + sqrt(determinanta)) / (2 * a);
            std::cout << "Prvo rjesenje kvadratne jednacine je: " << x1 << std::endl;

            double x2;
            x2 = (-b - sqrt(determinanta)) / (2 * a);
            std::cout << "Drugo rjesenje kvadratne jednacine je: " << x2 << std::endl;        
        }
        else {
            std::cout << "Prvo rjesenje kvadratne jednacine je: " << -b / (2 * a) << " + i*" 
            << std::abs(std::sqrt(std::abs(determinanta)) / (2 * a)) << std::endl;
            
            std::cout << "Drugo rjesenje kvadratne jednacine je: " << -b / (2 * a) << " - i*" 
            << std::abs(std::sqrt(std::abs(determinanta)) / (2 * a)) << std::endl;       
        }
    }
    else if( a == 0 && b != 0 ) {
        std::cout << "Rjesenje je: " << -c / b << std::endl; 
    }
    else {
        std::cout << "Data jednacina nema rjesenja.";
    }
    
    return 0;
}