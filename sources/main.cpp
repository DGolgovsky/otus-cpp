#include "bulk.h"

int main(int argc, char **argv)
{
    std::size_t cmds_count = 0;

    if (argc > 1) {
        cmds_count = static_cast<size_t>(atoi(argv[1])); // NOLINT
    } else {
        std::cerr << "Bad input. Need at least one argument." << std::endl;
        return 2;
    }

    Bulk blk(cmds_count);
    std::string cmd;

    while (std::getline(std::cin, cmd)) {
        blk.read_cmds(cmd);
    }

    blk.write_cmds();

    return 0;
}
