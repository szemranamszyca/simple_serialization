#include <iostream>
#include "Person.h"

int main()
{
    Person p;

    p.changeForTest();
    p.serialize();

    Person b;
    b.deserialize();

    std::cout << "Before\n\n";
    std::cout << p;
    std::cout << "After\n\n";
    std::cout << b;


    return 0;
}