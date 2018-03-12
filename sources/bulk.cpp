#include "bulk.h"

void Bulk::read_cmds(std::string command)
{
    if (first_cmd) {
        timestamp = std::to_string(std::time(nullptr));
        first_cmd = false;
    }

    if (command == "{") {
        brackets.push_back('{');
        if (brackets.size() == 1) {
            write_cmds();
        }
        return;
    } else if (command == "}") {
        brackets.pop_back();
        if (!brackets.empty()) return;
        else {
            write_cmds();
            return;
        }
    }

    bulk.push_back(command);
    if (!(bulk.size() != n || !brackets.empty())) {
        write_cmds();
    }
}

void Bulk::write_cmds()
{
    dynamic_cast<FileWriter *>(file_wrtr)->set_timestamp(timestamp);

    console_wrtr->write(bulk);
    file_wrtr->write(bulk);

    timestamp.clear();
    first_cmd = true;

    bulk.clear();
}

Bulk::~Bulk() {
    delete(file_wrtr);
    delete(console_wrtr);
}

Bulk::Bulk(std::size_t _n)
        : n(_n)
{
    console_wrtr = new ConsoleWriter();
    file_wrtr = new FileWriter();
}
