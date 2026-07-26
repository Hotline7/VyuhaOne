#include "vyuhaone/version.hpp"

#include <iostream>

int main()
{
    std::cout << "VyuhaOne " << vyuhaone::version() << '\n';
    return 0;
}