// Write a function template named mult() that allows the user to multiply one value of any type (first parameter) and an integer (second parameter). The second parameter should not be a template type. The function should return the same type as the first parameter. The following program should run:

// #include <iostream>

// // write your mult function template here

// int main()
// {
// 	std::cout << mult(2, 3) << '\n';
// 	std::cout << mult(1.2, 3) << '\n';

// 	return 0;
// }

// and produce the following output:
// 6
// 3.6


#include <iostream>

template <typename T>
T mult(T x, int y)
{
    return x * y;
}

int main()
{
	std::cout << mult(2, 3) << '\n';
	std::cout << mult(1.2, 3) << '\n';

	return 0;
}