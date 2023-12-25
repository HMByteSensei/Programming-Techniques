#include <iostream>

int main() {
    std::cout << "Unesite broj: ";
    int br;
    std::cin >> br;
    for(int i=2; i<br; i++)
    {
        if(br % i == 0)
        {
            br /= i;
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;
    return 0;
}