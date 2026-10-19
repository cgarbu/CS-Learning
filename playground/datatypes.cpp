#include <iostream>
#include <bitset> 
#include <string> 

using namespace std::literals::string_literals;

int main()
{
    [[maybe_unused]] using Int3Bit = std::bitset<3>;     // Can represent 0 to 7 
    [[maybe_unused]] using Int24Bit = std::bitset<24>;   
    [[maybe_unused]] using Int99Bit = std::bitset<99>;   
    [[maybe_unused]] using Int1Bit = std::bitset<1>;     // Can represent 0 to 1

    Int3Bit zero{ 0 };
    std::cout << zero.to_ullong() << '\n';

    Int24Bit sevenHundred{ 700 };
    std::cout << sevenHundred.to_ullong() << '\n';

    return 0;
}