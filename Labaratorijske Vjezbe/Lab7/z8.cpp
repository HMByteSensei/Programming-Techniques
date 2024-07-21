#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>

std::string IzvrniBezRazmaka(std::string recenica) {
    std::string rez;//(recenica.size() - (std::count(recenica.begin(), recenica.end(), ' ')), 'x');
    std::remove_copy(recenica.rbegin(), recenica.rend(), std::back_inserter(rez), ' ');
    return rez;
}

int main ()
{

    std::string s{"Evo pada kiša."};
    std::cout << IzvrniBezRazmaka(s);
	return 0;
}
