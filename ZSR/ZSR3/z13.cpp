#include <iostream>

int main() {
    std::cout << "Unesite realan broj x, a potop prirodan broj n: ";
    double x;
    std::cin >> x; 
    int n;
    std::cin >> n;
    double S = 0;
    double m_1 = -1;
    for(int i=1; i<=n; i++) {
        if(i != 1) {
            m_1 *= (-1);
        }
        S += (m_1 / ( x * (x + i) ));
    }
    std::cout << S << std::endl;
    return 0;
}