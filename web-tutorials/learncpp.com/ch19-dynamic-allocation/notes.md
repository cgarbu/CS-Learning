## 19.1 Dynamic memory allocation with new and delete
* Operators new and delete allow us to dynamically allocate single variables for our programs.
* Dynamically allocated memory has dynamic duration and will stay allocated until you deallocate it or the program terminates.
* Be careful not to perform dereference a dangling or null pointers.

1. C++ supports three basic types of memory allocation:
* Static memory allocation happens for static and global variables. Alocated once the program is run and persists throughout its life.
* Automatic memory allocation happens for function parameters and local variables. Memory for these types of variables is allocated when the relevant block is entered, and freed when the block is exited, as many times as necessary.
* Dynamic memory allocation is the topic of this article.

2. Both static and automatic allocation have two things in common:
* The size of the variable / array must be known at compile time.
* Memory allocation and deallocation happens automatically (when the variable is instantiated / destroyed).

3. To allocate a single variable dynamically, we use the scalar (non-array) form of the new operator:
> new int; // dynamically allocate an integer (and discard the result)
In the above case, we’re requesting an integer’s worth of memory from the operating system. The new operator creates the object using that memory, and then returns a pointer containing the address of the memory that has been allocated.

Most often, we’ll assign the return value to our own pointer variable so we can access the allocated memory later.
> int* ptr{ new int }; // dynamically allocate an integer and assign the address to ptr so we can access it later

We can then dereference the pointer to access the memory:
> *ptr = 7; // assign value of 7 to allocated memory

Note that accessing heap-allocated objects is generally slower than accessing stack-allocated objects. Because the compiler knows the address of stack-allocated objects, it can go directly to that address to get a value. Heap allocated objects are typically accessed via pointer. This requires two steps: one to get the address of the object (from the pointer), and another to get the value.

4. Unlike static or automatic memory, the program itself is responsible for requesting and disposing of dynamically allocated memory.

5. The allocation and deallocation for stack objects is done automatically. There is no need for us to deal with memory addresses -- the code the compiler writes can do this for us. The allocation and deallocation for heap objects is not done automatically. We need to be involved. That means we need some unambiguous way to refer to a specific heap allocated object, so that we can request its destruction when we’re ready. And the way we reference such objects is via memory address.

When we use operator new, it returns a pointer containing the memory address of the newly allocated object. We generally want to store that in a pointer so we can use that address later to access the object (and eventually, request its destruction).

6. When you dynamically allocate a variable, you can also initialize it via direct initialization or uniform initialization:
> int* ptr1{ new int (5) }; // use direct initialization
> int* ptr2{ new int { 6 } }; // use uniform initialization

7. When we are done with a dynamically allocated variable, we need to explicitly tell C++ to free the memory for reuse. For single variables, this is done via the scalar (non-array) form of the delete operator:
> // assume ptr has previously been allocated with operator new
> delete ptr; // return the memory pointed to by ptr to the operating system
> ptr = nullptr; // set ptr to be a null pointer

Note that the delete operator does not actually delete anything. It simply returns the memory being pointed to back to the operating system.

A pointer that is pointing to deallocated memory is called a dangling pointer.

8. When requesting memory from the operating system, in rare circumstances, the operating system may not have any memory to grant the request with.

By default, if new fails, a bad_alloc exception is thrown. If this exception isn’t properly handled (and it won’t be, since we haven’t covered exceptions or exception handling yet), the program will simply terminate (crash) with an unhandled exception error.

In many cases, having new throw an exception (or having your program crash) is undesirable, so there’s an alternate form of new that can be used instead to tell new to return a null pointer if memory can’t be allocated. This is done by adding the constant std::nothrow between the new keyword and the allocation type:

> int* value { new (std::nothrow) int }; // value will be set to a null pointer if the integer allocation fails

Or 

> int* value { new (std::nothrow) int{} }; // ask for an integer's worth of memory
> if (!value) // handle case where new returned null
> {
>    // Do error handling here
>    std::cerr << "Could not allocate memory\n";
> }

9. Deleting a null pointer is okay, and does nothing. There is no need to conditionalize your delete statements.

10. Memory leaks happen when your program loses the address of some bit of dynamically allocated memory before giving it back to the operating system. When this happens, your program can’t delete the dynamically allocated memory, because it no longer knows where it is (e.g. because the variable holding the address is out of scope). 


## 19.2 Dynamically allocating arrays

1. To allocate an array dynamically, we use the array form of new and delete (often called new[] and delete[]):
> int* array{ new int[length]{} };
> delete[] array; 

The length of dynamically allocated arrays has type std::size_t.

When deleting a dynamically allocated array, we have to use the array version of delete, which is delete[]. This tells the CPU that it needs to clean up multiple variables instead of a single variable. Using the scalar version of delete on an array will result in undefined behavior. 

2. If you want to initialize a dynamically allocated array to 0, the syntax is quite simple:
> int* array{ new int[length]{} };

Starting with C++11, it’s now possible to initialize dynamic arrays using initializer lists!
> int fixedArray[5] = { 9, 7, 5, 3, 1 }; // initialize a fixed array before C++11
> int* array{ new int[5]{ 9, 7, 5, 3, 1 } }; // initialize a dynamic array since C++11
> // To prevent writing the type twice, we can use auto. This is often done for types with long names.
> auto* array{ new int[5]{ 9, 7, 5, 3, 1 } };
Note that this syntax has no operator= between the array length and the initializer list.

For consistency, fixed arrays can also be initialized using uniform initialization:
> int fixedArray[]{ 9, 7, 5, 3, 1 }; // initialize a fixed array in C++11
> char fixedArray[]{ "Hello, world!" }; // initialize a fixed array in C++11
> Explicitly stating the size of the array is optional.


## 19.3 Destructors

1. A destructor is another special kind of class member function that is executed when an object of that class is destroyed. Whereas constructors are designed to initialize a class, destructors are designed to help clean up.

When an object goes out of scope normally, or a dynamically allocated object is explicitly deleted using the delete keyword, the class destructor is automatically called (if it exists) to do any necessary clean up before the object is removed from memory. For simple classes (those that just initialize the values of normal member variables), a destructor is not needed because C++ will automatically clean up the memory for you.

However, if your class object is holding any resources (e.g. dynamic memory, or a file or database handle), or if you need to do any kind of maintenance before the object is destroyed, the destructor is the perfect place to do so, as it is typically the last thing to happen before the object is destroyed.

2. Like constructors, destructors have specific naming rules:
* The destructor must have the same name as the class, preceded by a tilde (~).
* The destructor can not take arguments.
* The destructor has no return type.

A class can only have a single destructor.

Generally you should not call a destructor explicitly (as it will be called automatically when the object is destroyed), since there are rarely cases where you’d want to clean up an object more than once. However, destructors may safely call other member functions since the object isn’t destroyed until after the destructor executes.

Example:
> ~IntArray() // destructor
> {
>   // Dynamically delete the array we allocated earlier
>   delete[] m_array;
> }

3. RAII (Resource Acquisition Is Initialization) is a programming technique whereby resource use is tied to the lifetime of objects with automatic duration (e.g. non-dynamically allocated objects). In C++, RAII is implemented via classes with constructors and destructors. A resource (such as memory, a file or database handle, etc…) is typically acquired in the object’s constructor (though it can be acquired after the object is created if that makes sense). That resource can then be used while the object is alive. The resource is released in the destructor, when the object is destroyed. The primary advantage of RAII is that it helps prevent resource leaks (e.g. memory not being deallocated) as all resource-holding objects are cleaned up automatically.

The IntArray class at the top of this lesson is an example of a class that implements RAII -- allocation in the constructor, deallocation in the destructor. std::string and std::vector are examples of classes in the standard library that follow RAII -- dynamic memory is acquired on initialization, and cleaned up automatically on destruction.

4. Note that if you use the std::exit() function, your program will terminate and no destructors will be called. Be wary if you’re relying on your destructors to do necessary cleanup work (e.g. write something to a log file or database before exiting).

## 19.4 Pointers to pointers and dynamic multidimensional arrays

1. A pointer to a pointer to an int is declared using two asterisks
> int** ptrptr; // pointer to a pointer to an int, two asterisks

A pointer to a pointer works just like a normal pointer — you can dereference it to retrieve the value pointed to. And because that value is itself a pointer, you can dereference it again to get to the underlying value. These dereferences can be done consecutively:
> int value { 5 };
> int* ptr { &value };
> std::cout << *ptr << '\n'; // Dereference pointer to int to get int value

> int** ptrptr { &ptr };
> std::cout << **ptrptr << '\n'; // dereference to get pointer to int, dereference again to get int value

Note that you can not set a pointer to a pointer directly to a value. This is because the address of operator (operator&) requires an lvalue, but &value is an rvalue.

However, a pointer to a pointer can be set to null:
> int** ptrptr { nullptr };

2. Pointers to pointers have a few uses. The most common use is to dynamically allocate an array of pointers:
> int** array { new int*[10] }; // allocate an array of 10 int pointers
This works just like a standard dynamically allocated array, except the array elements are of type “pointer to integer” instead of integer.

Another common use for pointers to pointers is to facilitate dynamically allocated multidimensional arrays. If the rightmost array dimension is constexpr, you can do this:
> int x { 7 }; // non-constant
> int (*array)[5] { new int[x][5] }; // rightmost dimension must be constexpr
The parenthesis are required so that the compiler knows we want array to be a pointer to an array of 5 int (which in this case is the first row of a 7-row multidimensional array). Without the parenthesis, the compiler would interpret this as int* array[5], which is an array of 5 int*.

This is a good place to use automatic type deduction:
> int x { 7 }; // non-constant
> auto array { new int[x][5] }; // so much simpler!
Unfortunately, this relatively simple solution doesn’t work if the rightmost array dimension isn’t a compile-time constant. In that case, we have to get a little more complicated. First, we allocate an array of pointers (as per above). Then we iterate through the array of pointers and allocate a dynamic array for each array element. Our dynamic two-dimensional array is a dynamic one-dimensional array of dynamic one-dimensional arrays!

> int** array { new int*[10] }; // allocate an array of 10 int pointers — these are our rows
> for (int count { 0 }; count < 10; ++count)
>    array[count] = new int[5]; // these are our columns

We can then access our array like usual:
> array[9][4] = 3; // This is the same as (array[9])[4] = 3;

Deallocating a dynamically allocated two-dimensional array using this method requires a loop as well -- we must delete in the opposite order of creation. 

3. It’s also possible to declare a pointer to a pointer to a pointer. Or a pointer to a pointer to a pointer to a pointer to a pointer. 

4. Avoid pointers to pointers unless there are no other options.


## 19.5 Void pointers

1. The void pointer, also known as the generic pointer, is a special type of pointer that can be pointed at objects of any data type! A void pointer is declared like a normal pointer, using the void keyword as the pointer’s type:
> void* ptr {}; // ptr is a void pointer

2. A void pointer can point to objects of any data type. 

3. However, because the void pointer does not know what type of object it is pointing to, dereferencing a void pointer is illegal. Instead, the void pointer must first be cast to another pointer type before the dereference can be performed, e.g.:
> int* intPtr{ static_cast<int*>(voidPtr) };

4. Void pointers can be set to a null value.

5. Because a void pointer does not know what type of object it is pointing to, deleting a void pointer will result in undefined behavior. If you need to delete a void pointer, static_cast it back to the appropriate type first. It is not possible to do pointer arithmetic on a void pointer.

6. Note that there is no such thing as a void reference. This is because a void reference would be of type void &, and would not know what type of value it referenced.

7. A void pointer is a pointer that can point to any type of object, but does not know what type of object it points to. A void pointer must be explicitly cast into another type of pointer to perform indirection. A null pointer is a pointer that does not point to an address. A void pointer can be a null pointer. Thus, a void pointer refers to the type of the pointer, whereas a null pointer refers to the value (address) of the pointer.