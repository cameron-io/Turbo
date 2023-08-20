#include <iostream>
#include "lib/oop/object_copy.hpp"

std::ostream& operator<<(
    std::ostream& stream,
    const String& string)
{
    stream << string.m_Buffer;
    return stream;
}

/*
    In most cases, an object must be passed in by
    (const) reference, to prevent unnecessary copies
    unless explicitly required
*/
void SomeFunction(const String& string)
{
    std::cout << string << std::endl;
}

int object_copy_test()
{
    String first = "test";
    String second = first;

    // Must not update first variable
    second[2] = 'n';

    SomeFunction(first);
    SomeFunction(second);

    std::cout << first << std::endl;
    std::cout << second << std::endl;

    return 0;
}

int main()
{
    return object_copy_test();
}