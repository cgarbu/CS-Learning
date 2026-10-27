// Do not use std::bitset in this quiz. We’re only using std::bitset for printing.

// a) Add a line of code to set the article as viewed.
// Expected output:
// 00000101

// b) Add a line of code to check if the article was deleted.

// c) Add a line of code to clear the article as a favorite.
// Expected output (Assuming you did quiz (a)):
// 00000001

#include <bitset>
#include <cstdint>
#include <iostream>

int main()
{
    [[maybe_unused]] constexpr std::uint8_t option_viewed{ 0x01 };      // hex for 0000 0001
    [[maybe_unused]] constexpr std::uint8_t option_edited{ 0x02 };      // hex for 0000 0010
    [[maybe_unused]] constexpr std::uint8_t option_favorited{ 0x04 };   // hex for 0000 0100
    [[maybe_unused]] constexpr std::uint8_t option_shared{ 0x08 };      // hex for 0000 1000
    [[maybe_unused]] constexpr std::uint8_t option_deleted{ 0x10 };     // hex for 0001 0000

    std::uint8_t myArticleFlags{ option_favorited }; // Represented as 0000 0100

    // Solution for a)
    myArticleFlags |= option_viewed; 
    std::cout << std::bitset<8>{ myArticleFlags } << '\n';

    // Solution for b)
    if (myArticleFlags & option_deleted) ; 

    // Solution for c)
    myArticleFlags ^= option_favorited; // Produces desired outcome, but not correct
    myArticleFlags &= ~option_favorited; // Correct
    std::cout << std::bitset<8>{ myArticleFlags } << '\n';

    return 0;
}