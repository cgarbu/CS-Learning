// Write a function named sumTo() that takes an integer parameter named value, and returns the sum of all the numbers from 1 to value.

// For example, sumTo(5) should return 15, which is 1 + 2 + 3 + 4 + 5.

// Hint: Use a non-loop variable to accumulate the sum as you iterate from 1 to the input value, much like the pow() example above uses the total variable to accumulate the return value each iteration.

int sumTo(int value)
{
    int sum{ 0 };
    for (int i{ 1 }; i <= value; i++)
        sum += i;

    return sum; 
}