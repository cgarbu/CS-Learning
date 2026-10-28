// Write a class template named Triad that has 3 private data members with independent type template parameters. The class should have a constructor, access functions, and a print() member function that is defined outside the class.

// The following program should compile and run:

// #include <iostream>
// #include <string>

// int main()
// {
// 	Triad<int, int, int> t1{ 1, 2, 3 };
// 	t1.print();
// 	std::cout << '\n';
// 	std::cout << t1.first() << '\n';

// 	using namespace std::literals::string_literals;
// 	const Triad t2{ 1, 2.3, "Hello"s };
// 	t2.print();
// 	std::cout << '\n';

// 	return 0;
// }

// and produce the output:
// [1, 2, 3]
// 1
// [1, 2.3, Hello]

#include <iostream>
#include <string>

template <typename T, typename U, typename V>
class Triad
{
private:
    T m_first{ 0 };
    U m_second{ 0 };
    V m_third{ 0 }; 

public: 
    Triad() = default; 

    Triad(const T& first, const U& second, const V& third)
        : m_first { first }
        , m_second { second }
        , m_third { third }
    {
    }

    auto& first() const { return m_first; };
    auto& second() const { return m_second; };
    auto& third() const { return m_third; }; 

    // const T& first() const { return m_first; }
	// const U& second() const { return m_second; }
	// const V& third() const { return m_third; }

    // void print() const;

    void print() const
    {
        std::cout << "[" << m_first << ", " << m_second << ", " << m_third << "]\n";
    }

    ~Triad()
    {
    }
};

// template <typename T, typename U, typename V>
// void Triad<T, U, V>::print() const
// {
// 	std::cout << '[' << m_first << ", " << m_second << ", " << m_third << ']' ;
// }

int main()
{
	Triad<int, int, int> t1{ 1, 2, 3 };
	t1.print();
	std::cout << '\n';
	std::cout << t1.first() << '\n';

	using namespace std::literals::string_literals;
	const Triad t2{ 1, 2.3, "Hello"s };
	t2.print();
	std::cout << '\n';

	return 0;
}