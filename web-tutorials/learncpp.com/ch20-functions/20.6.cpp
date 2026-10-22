// Create a struct Student that stores the name and points of a student. Create an array of students and use std::max_element to find the student with the most points, then print that student’s name. std::max_element takes the begin and end of a list, and a function that takes 2 parameters and returns true if the first argument is less than the second.

// Given the following array

// std::array<Student, 8> arr{
//   { { "Albert", 3 },
//     { "Ben", 5 },
//     { "Christine", 2 },
//     { "Dan", 8 }, // Dan has the most points (8).
//     { "Enchilada", 4 },
//     { "Francis", 1 },
//     { "Greg", 3 },
//     { "Hagrid", 5 } }
// };
// your program should print

// Dan is the best student

#include <array> 
#include <iostream>
#include <string>
#include <string_view> 

struct Student
{
    std::string student_name{ };
    int student_points{ };
};

int main()
{
    std::array<Student, 8> arr{
    { { "Albert", 3 },
        { "Ben", 5 },
        { "Christine", 2 },
        { "Dan", 8 }, // Dan has the most points (8).
        { "Enchilada", 4 },
        { "Francis", 1 },
        { "Greg", 3 },
        { "Hagrid", 5 } }
    };

     
    auto isLessThan = [] (Student a, Student b) {
        return a.student_points < b.student_points;
    };

    //   learncpp.com's lambda.
    //       const auto best {
    //     std::max_element(arr.begin(), arr.end(), [](const auto& a, const auto& b) {
    //       return a.points < b.points;
    //     })
    //   };

    auto result { std::max_element(arr.begin(), arr.end(), isLessThan) }; 

    // This iterator points to the Student with the most points.
    // Using -> to access that student's student_name member.
    std::cout << result->student_name << " is the best student.";
    
    return 0;
}