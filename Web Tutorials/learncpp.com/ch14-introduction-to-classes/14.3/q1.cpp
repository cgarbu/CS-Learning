// Create a struct called IntPair that holds two integers. Add a member function named print that prints the value of the two integers.

// The following program function should compile:

// #include <iostream>

// // Provide the definition for IntPair and the print() member function here

// int main()
// {
// 	IntPair p1 {1, 2};
// 	IntPair p2 {3, 4};

// 	std::cout << "p1: ";
// 	p1.print();

// 	std::cout << "p2: ";
// 	p2.print();

// 	return 0;
// }

// and produce the output:
// p1: Pair(1, 2)
// p2: Pair(3, 4)

#include <iostream>

struct IntPair
{
    int intOne{ };
    int intTwo{ };

    void print()
    { 
        std::cout << "Pair (" << intOne << ", " << intTwo << ")\n";
    }
};

int main()
{
	IntPair p1 {1, 2};
	IntPair p2 {3, 4};

	std::cout << "p1: ";
	p1.print();

	std::cout << "p2: ";
	p2.print();

	return 0;
}