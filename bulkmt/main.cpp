#include "blk.h"

int main(int argc, char **argv)
{
    if (argc > 1) {
        auto bulk = std::make_shared<blk>(std::stoi(argv[1]));
        bulk->exec();
    } else {
        std::cerr << "Needed at least one argument.\n";
    }

    return 0;
}