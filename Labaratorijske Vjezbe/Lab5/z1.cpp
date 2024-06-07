#include <iostream>
int main ()
{
    char recenica[200];
    std::cout << "Unesite recenicu: ";
    std::cin.getline(recenica, 200);
    char *p = recenica;
    while(*p==' ') p++;
    while(*p != '\0' && *p != ' ') p++;
    //p++;
    while(*p==' ') p++;
    std::cout << "Recenica bez prve rijeci glasi: ";
    while(*p != '\0')
    {
        std::cout << *p;
        p++;
    }
    std::cout << std::endl;
	return 0;
}