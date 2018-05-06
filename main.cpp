#include "sources/async.h"

#include <string>
#include <iostream>
#include <thread>

int main(int argc, char **argv)
{
    std::size_t bulk = 5;
    auto h = async::connect(bulk);
    auto h2 = async::connect(bulk);
    async::receive(h, "1", 1);
    async::receive(h2, "1\n", 2);
    async::receive(h, "\n2\n3\n444\n5\n6\n{\na\n", 15);
    async::receive(h, "b\nc\nd\n}\n89\n", 11);
    async::disconnect(h);
    async::disconnect(h2);
    
    auto h3 = async::connect(3);
    auto t1 = std::thread( [&] () {
        for (int i = 0; i < 10000; i += 2) {
            std::string cmd = "cmd" + std::to_string(i) + "\n";
            async::receive(h3, cmd.c_str(), cmd.length());
        }
    });
    
    auto t2 = std::thread([&] () {
        for (int i = 1; i <= 10000; i += 2) {
            std::string cmd = "cmd" + std::to_string(i) + "\n";
            async::receive(h3, cmd.c_str(), cmd.length());
        }
    });
    
    t1.join();
    t2.join();
    
    async::disconnect(h3);
    
    return 0;
}
