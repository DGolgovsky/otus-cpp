#include "blk.h"

using namespace std::chrono_literals;

blk::blk(std::size_t block_size)
        : m_block_size(block_size)
{
    meter::instance().reg_thread(m_thread_name);

    subscribe(std::make_shared<console_log>());
    subscribe(std::make_shared<file_log>(file_log_count));
}

void blk::exec()
{
    start_watcher();

    std::string command;
    while (std::getline(std::cin, command)) {
        meter::instance().lines_incr(m_thread_name);
        proc_cmd(command);
    }
    force_dump();

    stop_watcher();

    meter::instance().prnt_meter();
}

void blk::proc_cmd(const std::string &cmd)
{
    if (cmd == "{") {
        proc_bgn_brace();
    } else if (cmd == "}") {
        proc_end_brace();
    } else {
        proc_smpl_cmd(cmd);
    }
}

void blk::force_dump()
{
    if (!m_braces_count) {
        notify();
    }
}

void blk::start_watcher()
{
    for(auto& watch : m_subs)
        watch->start();
}

void blk::stop_watcher()
{
    for(auto& watch : m_subs)
        watch->stop();
}

void blk::subscribe(std::shared_ptr<watcher>&& watch)
{
    m_subs.emplace_back(std::move(watch));
}

void blk::proc_bgn_brace()
{
    m_braces_count++;
    if (m_braces_count == 1) {
        notify();
        m_storage.init_time();
    }
}

void blk::proc_end_brace()
{
    m_braces_count--;
    if (!m_braces_count) {
        notify();
    }
}

void blk::proc_smpl_cmd(const std::string &cmd)
{
    if (!m_storage.commands_count())
        m_storage.init_time();

    m_storage.add(cmd);
    if ((!m_braces_count) &&
        (m_storage.commands_count() == m_block_size)) {
        notify();
    }
}

void blk::notify()
{
    if (!m_storage.is_empty()) {
        block_t cmd = m_storage.make_block(meter::instance().get_blocks_cnt(m_thread_name));
        for (auto &s : m_subs)
            s->update(cmd);

        meter::instance().blocks_incr(m_thread_name);
        meter::instance().cmds_incr(m_thread_name, cmd.count);

        m_storage.clear();
    }
}
