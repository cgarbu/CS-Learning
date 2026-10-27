// Write a program that prints out the letters a through z along with their ASCII codes. Use a loop variable of type char.

#include <iomanip> 
#include <iostream> 

int main()
{
    char ch{'a'};
    while (ch <= 'z')
    {
        std::cout << ch << std::setw(10) << static_cast<int>(ch) << '\n';
        ++ch; 
    }

    return 0; 
}