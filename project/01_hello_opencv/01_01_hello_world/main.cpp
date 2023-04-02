#include <iostream>

int main()
{
    int value = 5; // normal integer
    int value1 = 100;
    int& ref = value; // reference to variable value

    value = 6; // value is now 6
    ref = 7;   // value is now 7

    std::cout << value << std::endl; // prints 7
    ++ref;
    std::cout << value<< std::endl; // prints 8
    ref = value1;
    ++ref;
    std::cout << value << std::endl; // prints 7
    std::cout << value1 << std::endl;
    std::cout << ref << std::endl;


    return 0;
}