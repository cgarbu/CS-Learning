// Invert the nested loops example so it prints the following:
// 5 4 3 2 1
// 4 3 2 1
// 3 2 1
// 2 1
// 1

// Output before changes:
// 1
// 1 2
// 1 2 3
// 1 2 3 4
// 1 2 3 4 5

#include <iostream>

int main()
{
    int outer{ 5 };
    while (outer >= 1)
    {
        int inner{ outer };
        while (inner >= 1)
        {
            std::cout << inner-- << ' ';
        }

        std::cout << '\n';
        --outer; 
    }

    return 0;
}
