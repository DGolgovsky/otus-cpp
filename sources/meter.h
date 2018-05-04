#pragma once

#include <atomic>
#include <thread>
#include <map>
#include <iostream>
#include <utility>

using namespace std::chrono;

struct thread_metricks
{
    std::string thread_id;
    std::shared_ptr<std::atomic<int>> lines = std::make_shared<std::atomic<int>>(0);
    std::shared_ptr<std::atomic<int>> blocks = std::make_shared<std::atomic<int>>(0);
    std::shared_ptr<std::atomic<int>> commands = std::make_shared<std::atomic<int>>(0);

    explicit thread_metricks(std::string thr_id)
            : thread_id(std::move(thr_id))
    { }
};

class meter
{
public:
    static meter& instance();
    void reg_thread(const std::string &thread_id);
    int get_lines_count(const std::string &thread_id) const;
    void lines_incr(const std::string &thread_id);
    int get_blocks_cnt(const std::string &thread_id) const;
    void blocks_incr(const std::string &thread_id);
    void cmds_incr(const std::string &thread_id, unsigned long commands);
    void prnt_meter();

    milliseconds get_time_now();
    milliseconds get_diff_time_now(const milliseconds& start);
    void prnt_time(const milliseconds &time);

    meter(const meter& root) = delete;
    meter& operator=(const meter&) = delete;

private:
    meter() = default;

    std::map<std::string, thread_metricks> m_meter;
};
