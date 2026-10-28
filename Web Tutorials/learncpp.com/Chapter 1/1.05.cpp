#include <iostream>

int main() 
{
    std::cout << "Enter three numbers: ";
    
    int a{}, b{}, c{};
    std::cin >> a >> b >> c;

    std::cout << "You entered " << a << ", " << b << ", and " << c << ".";
    
    return 0;
}