// Sample output:

// Mary has a few apples.
// How many apples do you have? 1
// You have a single apple.
// getQuantityPhrase() should take a single int parameter representing the quantity of something and return the following descriptor:

// < 0 = “negative”
// 0 = “no”
// 1 = “a single”
// 2 = “a couple of”
// 3 = “a few”
// > 3 = “many”
// getApplesPluralized() should take a single int parameter parameter representing the quantity of apples and return the following:

// 1 = “apple”
// otherwise = “apples”
// This function should use the conditional operator.


#include <iostream>

// Write the function getQuantityPhrase() here

constexpr std::string getQuantityPhrase(int maryApples)
{
    if (maryApples < 0)
        return "negative";
    else if (maryApples == 0)
        return "no";
    else if (maryApples == 1)
        return "a single";
    else if (maryApples == 2)
        return "a couple of";
    else if (maryApples == 3)
        return "a few";
    else if (maryApples > 3)
        return "many";
}

// Write the function getApplesPluralized() here

constexpr std::string getApplesPluralized(int maryApples)
{
    return maryApples == 1 ? "apple" : "apples";
}

int main()
{
    constexpr int maryApples { 3 };
    std::cout << "Mary has " << getQuantityPhrase(maryApples) << ' ' << getApplesPluralized(maryApples) << ".\n";

    std::cout << "How many apples do you have? ";
    int numApples{};
    std::cin >> numApples;

    std::cout << "You have " << getQuantityPhrase(numApples) << ' ' << getApplesPluralized(numApples) << ".\n";

    return 0;
}