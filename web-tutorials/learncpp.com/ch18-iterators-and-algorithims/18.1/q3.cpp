// This one is going to be difficult, so put your game face on.

// Another simple sort is called “bubble sort”. Bubble sort works by comparing adjacent pairs of elements, and swapping them if the criteria is met, so that elements “bubble” to the end of the array. Although there are quite a few ways to optimize bubble sort, in this quiz we’ll stick with the unoptimized version here because it’s simplest.

// Unoptimized bubble sort performs the following steps to sort an array from smallest to largest:
// A) Compare array element 0 with array element 1. If element 0 is larger, swap it with element 1.
// B) Now do the same for elements 1 and 2, and every subsequent pair of elements until you hit the end of the array. At this point, the last element in the array will be sorted.
// C) Repeat the first two steps again until the array is sorted.

// Write code that bubble sorts the following array according to the rules above:

// int array[]{ 6, 3, 2, 9, 7, 1, 5, 4, 8 };
// Print the sorted array elements at the end of your program.

// Hint: If we’re able to sort one element per iteration, that means we’ll need to iterate roughly as many times as there are numbers in our array to guarantee that the whole array is sorted.
// Hint: When comparing pairs of elements, be careful of your array’s range.

#include <iostream>
#include <utility>

int main()
{
    int array[]{ 6, 3, 2, 9, 7, 1, 5, 4, 8 };
    constexpr int length{ static_cast<int>(std::size(array)) };

    for (int startIndex{ 0 }; startIndex < length; ++startIndex)
    {
        for (int currentIndex{ startIndex + 1 }; currentIndex < length; ++currentIndex)
        {
            if (array[startIndex] > array[currentIndex])
                std::swap(array[startIndex], array[currentIndex]);
        }
    }

	for (int index{ 0 }; index < length; ++index)
		std::cout << array[index] << ' ';

	std::cout << '\n';

    return 0;
}