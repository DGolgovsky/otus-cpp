#include "writer.h"

void ConsoleWriter::write(std::vector<std::string> &bulk)
{
    for (auto &&element : bulk) {
        std::cout << element << " ";
    }

    std::cout << std::endl;
}

void FileWriter::write(std::vector<std::string> &bulk)
{
    if (bulk.empty()) return;

    std::ofstream out("bulk" + timestamp + ".log");

    for (auto &&element : bulk) {
        out << element << " ";
    }
    out << std::endl;

    out.close();
}

void FileWriter::set_timestamp(std::string t)
{
    timestamp = std::move(t);
}
