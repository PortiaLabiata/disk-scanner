#include <iostream>
#include "channel.hpp"

int main(int argc, char **argv)
{
    prims::channel<int, 16> channel;
    std::cout << "Hello, world!" << std::endl;
    return 0;
}
