#include <iostream>
#include <cmath>
#include <functional>

std::function<double(double)> plus2 (double x) {
    return [x](double y) { return x + y; };
}

std::function<std::function<double(double)>(double)> plus3 (double x) {
    return [x](double y) { return [x, y](double z) {return x+y+z;}; };
}

int main ()
{
    int a{5}, b{10}, c{100};
    std::cout << "Plus2: " << plus2(a)(b);
    std::cout << "\nPlus3: " << plus3(a)(b)(c) << "\n"; 

	return 0;
}
