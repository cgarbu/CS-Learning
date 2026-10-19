// Write a program that pushes and pops values, and outputs the following sequence:
//        (Stack: empty)
// Push 1 (Stack: 1)
// Push 2 (Stack: 1 2)
// Push 3 (Stack: 1 2 3)
// Pop    (Stack: 1 2)
// Push 4 (Stack: 1 2 4)
// Pop    (Stack: 1 2)
// Pop    (Stack: 1)
// Pop    (Stack: empty)

#include <iostream>
#include <vector>

void printStackValues(const std::vector<int>& v)
{
    std::cout << "\t(Stack:";

    for (auto e : v)
        std::cout << ' ' << e;

    if (v.empty()) 
        std::cout << " empty";

    std::cout << ")\n";
}

void pushAndPrint(std::vector<int>& v, int val)
{
    v.push_back(val);
    std::cout << "Push " << val;
    printStackValues(v);
}

void popAndPrint(std::vector<int>& v)
{
    v.pop_back();
    std::cout << "Pop ";
    printStackValues(v);
}

int main()
{
    std::vector<int> v {};

    printStackValues(v);

    pushAndPrint(v, 1);
    pushAndPrint(v, 2);
    pushAndPrint(v, 3);
    popAndPrint(v);
    pushAndPrint(v, 4);
    popAndPrint(v);
    popAndPrint(v);
    popAndPrint(v);

    return 0;
}