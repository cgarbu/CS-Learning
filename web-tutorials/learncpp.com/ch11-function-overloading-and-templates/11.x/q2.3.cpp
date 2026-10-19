// Write a function template named sub() that allows the user to subtract two values of different types. The following program should run:

// #include <iostream>

// // write your sub function template here

// int main()
// {
// 	std::cout << sub(3, 2) << '\n';
// 	std::cout << sub(3.5, 2) << '\n';
// 	std::cout << sub(4, 1.5) << '\n';

// 	return 0;
// }

// and produce the following output:
// 1
// 1.5
// 2.5


#include <iostream>

template <typename T, typename V> 
auto sub(T x, V y)
{
    return x - y;
}

/*
//If C++20 capable, you can use an abbreviated function template instead
auto sub(auto x, auto y)
{
	return x - y;
}
*/

int main()
{
	std::cout << sub(3, 2) << '\n';
	std::cout << sub(3.5, 2) << '\n';
	std::cout << sub(4, 1.5) << '\n';

	return 0;
}