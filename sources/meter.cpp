#include "meter.h"
#include <algorithm>

meter &meter::instance()
{
    static meter inst;
    return inst;
}

void meter::reg_thread(const std::string &thread_id)
{
    thread_metricks metr(thread_id);
    m_meter.emplace(std::move(std::make_pair(thread_id, std::move(metr))));
}

int meter::get_lines_count(const std::string& thread_id) const
{
    auto thr_metr = m_meter.find(thread_id);
    if (thr_metr != m_meter.end())
        return *(thr_metr->second.lines.get());

    return 0;
}

void meter::lines_incr(const std::string &thread_id)
{
    auto thr_metr = m_meter.find(thread_id);
    if (thr_metr != m_meter.end())
        *(thr_metr->second.lines.get()) += 1;
}

int meter::get_blocks_cnt(const std::string &thread_id) const
{
    auto thr_metr = m_meter.find(thread_id);
    if (thr_metr != m_meter.end())
        return *(thr_metr->second.blocks.get());

    return 0;
}

void meter::blocks_incr(const std::string &thread_id)
{
    auto thr_metr = m_meter.find(thread_id);
    if (thr_metr != m_meter.end())
        *(thr_metr->second.blocks.get()) += 1;
}

void meter::cmds_incr(const std::string &thread_id, unsigned long commands)
{
    auto thr_metr = m_meter.find(thread_id);
    if (thr_metr != m_meter.end())
        *(thr_metr->second.commands.get()) += commands;
}

void meter::prnt_meter()
{
    for (auto &metr : m_meter) {
        if (metr.first == "main")
            std::cout << metr.first
                      << ": lines: " << *(metr.second.lines)
                      << ", blocks: " << *(metr.second.blocks)
                      << ", cmds: " << *(metr.second.commands)
                      << std::endl;
        else
            std::cout << metr.first
                      << ": blocks: " << *(metr.second.blocks)
                      << ", cmds: " << *(metr.second.commands)
                      << std::endl;
    }
}

milliseconds meter::get_time_now()
{
    return duration_cast< milliseconds >(system_clock::now().time_since_epoch());
}

milliseconds meter::get_diff_time_now(const milliseconds &start)
{
    auto finish = meter::get_time_now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
}

void meter::prnt_time(const milliseconds &time)
{
    std::cout << "time: " << time.count() << " ms" << std::endl;
}
