#include <iostream>
#include <functional>

int main(int argc, char **argv)
{
    [out = std::ref(std::cout << "Hello, ")](){ out.get() << "World!\n"; }();

    return 0;
}

