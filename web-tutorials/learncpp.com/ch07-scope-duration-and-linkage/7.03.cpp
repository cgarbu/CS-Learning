// A variable’s scope determines where the variable is accessible within the source code. Duration defines the rules that govern when a variable is created and destroyed. A variable’s lifetime is the actual time between its creation and destruction.

// Local variables have block scope, which means they can be accessed from their point of definition to the end of the block they are defined within.

// Local variables have automatic duration, which means they are created at the point of definition, and destroyed at the end of the block in which they are defined.

// Write a program that asks the user to enter two integers, one named smaller, the other named larger. If the user enters a smaller value for the second integer, use a block and a temporary variable to swap the smaller and larger values. Then print the values of the smaller and larger variables. Add comments to your code indicating where each variable dies. Note: When you print the values, smaller should hold the smaller input and larger the larger input, no matter which order they were entered in.

// The program output should match the following:

// Enter an integer: 4
// Enter a larger integer: 2
// Swapping the values
// The smaller value is 2
// The larger value is 4

#include <iostream>

int main()
{
    std::cout << "Enter an integer: "; 
    int smaller{ }; 
    std::cin >> smaller;

    std::cout << "Enter a larger integer: ";
    int larger{ };
    std::cin >> larger; 

    if (larger < smaller)
    {
        std::cout << "Swapping the values" << '\n'; 

        int temp{ smaller }; 
        smaller = larger;
        larger = temp;  

        // is the same as
        // std::swap(larger, smaller);

    } // temp goes out of scope, and is then destroyed here

    std::cout << "The smaller value is " << smaller << '\n' << "The larger value is " << larger; 

    return 0;
} // smaller and larger go out of scope, and are then destroyed