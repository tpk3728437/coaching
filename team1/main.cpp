#include <iostream>
#include "calculator.h"

int main(int /*argc*/, char */*argv*/[])
{
    std::cout << "jee" << std::endl;

    std::cout << "1 plus 2 is " << calculator::plus(1,2) << std::endl;

    std::cout << "2 minus 1 is " << calculator::minus(2,1) << std::endl;

    std::cout << "3 minus 1 is " << calculator::minus(3,1) << std::endl;

    return 0;
}
