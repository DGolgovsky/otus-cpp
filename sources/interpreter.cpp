#include "interpreter.h"

interpreter::interpreter(size_t block_size)
    : m_block_size(block_size)
    , m_console_logger(std::make_shared<console_logger>())
    , m_file_logger(std::make_shared<file_logger>())
{
    subscribe(m_console_logger);
    subscribe(m_file_logger);
}

void interpreter::run()
{
    std::string command;

    while (std::getline(std::cin, command)) {
        process_cmd(command);
    }

    forced_dump();
}

void interpreter::process_cmd(const std::string &cmd)
{
    if (cmd == "{") {
        process_open_brace();
    } else if (cmd == "}") {
        process_close_brace();
    } else {
        process_simple_cmd(cmd);
    }
}

void interpreter::forced_dump()
{
    if (!m_braces_count) {
        notify();
    }
}

void interpreter::subscribe(std::shared_ptr<observer> obs)
{
    m_subs.push_back(obs);
}

void interpreter::process_open_brace()
{
    m_braces_count++;
    if (m_braces_count == 1) {
        notify();
        m_storage.init_time();
    }
}

void interpreter::process_close_brace()
{
    m_braces_count--;
    if (!m_braces_count) {
        notify();
    }
}

void interpreter::process_simple_cmd(const std::string &cmd)
{
    if (!m_storage.commands_count()) {
        m_storage.init_time();
    }

    m_storage.append(cmd);
    if ((!m_braces_count) && (m_storage.commands_count() == m_block_size)) {
        notify();
    }
}

void interpreter::notify()
{
    if (!m_storage.is_empty()) {
        cmd_pipe_t cmd = m_storage.make_pipe();
        for (auto &s : m_subs) {
            s->update(cmd);
        }
        m_storage.clear();
    }
}
