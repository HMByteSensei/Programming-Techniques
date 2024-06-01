#include <iostream>
#include <cmath>
#include <string>
#include <utility> 

void IzvrniString(std::string &recenica) {
    int brojac = 0;
    for(int i=recenica.size()-1; i>recenica.size()/2-1; i--) {
        // std::swap(recenica.at(i), recenica.at(brojac));
        char znak = recenica.at(brojac);
        recenica.at(brojac) = recenica.at(i);
        recenica.at(i) = znak; 
        brojac++;
    }
}
// Autor: MMuhamed Husić
int main ()
{   
    std::cout << "Unesi string: ";
    std::string s;
    std::getline(std::cin, s);
    IzvrniString(s);
    std::cout << "Izvrnuti string je: " << s << std::endl;
	return 0;
}