// a) Write a class named Point2d. Point2d should contain two member variables of type double: m_x, and m_y, both defaulted to 0.0.

// Provide a constructor and a print() function.

// The following program should run:

// #include <iostream>

// int main()
// {
//     Point2d first{};
//     Point2d second{ 3.0, 4.0 };

//     // Point2d third{ 4.0 }; // should error if uncommented

//     first.print();
//     second.print();

//     return 0;
// }

// This should print:
// Point2d(0, 0)
// Point2d(3, 4)

#include <iostream>

class Point2d
{
private:
    double m_x{ 0.0 };
    double m_y{ 0.0 };

public:
    Point2d() = default; 

    Point2d(double x, double y)
        : m_x{ x }
        , m_y{ y }
    {
    }

    void print() const 
    {
        std::cout << "Point2d(" << m_x << ", " << m_y << ")\n";
    }
};

int main()
{
    Point2d first{};
    Point2d second{ 3.0, 4.0 };

    // Point2d third{ 4.0 }; // should error if uncommented

    first.print();
    second.print();

    return 0;
}