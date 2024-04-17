#include <iostream>

int main() {
    std::cout << "Unesite broj: ";
    int broj;
    std::cin >> broj;
    if(!std::cin) std::exit(0);
    for(int i = 2; i<100; i++)
    {
        int prost = 1; //predpostavljamo da je broj i prost
        for(int j = 2; j<i; j++) //za testiranje da li je broj prost
        {
            if(broj == 0) break;
            if(i % j == 0) //broj i nije prost
            {
                prost = 0;
                break;
            }
        }
        if(broj == 0) break;
        if(prost && (broj % i == 0)) 
        {
            broj = broj / i;
            std::cout << i << " ";
            i--;
        }
    }
    std::cout << std::endl;
    return 0;
}