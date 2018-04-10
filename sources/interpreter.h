#pragma once

#include "storage.h"
#include <memory>

class interpreter
{
public:
    explicit interpreter(size_t block_size);

    void run();

    void process_cmd(const std::string &cmd);
    void forced_dump();

private:
    void subscribe(std::shared_ptr<observer> obs);

    void process_open_brace();
    void process_close_brace();
    void process_simple_cmd(const std::string &cmd);

    void notify();

    std::size_t m_block_size;
    std::shared_ptr<console_logger> m_console_logger;
    std::shared_ptr<file_logger> m_file_logger;
    std::vector<std::shared_ptr<observer>> m_subs;
    unsigned int m_braces_count = 0;
    storage m_storage;
};
