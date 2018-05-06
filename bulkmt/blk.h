#pragma once

#include "watcher.h"
#include "meter.h"
#include "file_log.h"
#include "console_log.h"
#include "storage.h"

#include <memory>
#include <vector>

const unsigned int file_log_count = 2;

class blk
{
public:
    explicit blk(size_t block_size);
    void exec();
    void proc_cmd(std::string const &cmd);
    void force_dump();
    void start_watcher();
    void stop_watcher();

private:
    void subscribe(std::shared_ptr<watcher> &&watch);
    void proc_bgn_brace();
    void proc_end_brace();
    void proc_smpl_cmd(std::string const &cmd);
    void notify();

    std::size_t m_block_size;
    std::vector<std::shared_ptr<watcher>> m_subs;
    int m_braces_count = 0;
    storage_t m_storage;

    std::string m_thread_name = "main";
};
