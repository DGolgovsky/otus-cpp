#pragma once

#include <fstream>
#include <sstream>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <thread>
#include <queue>
#include <iostream>

class file_log : public watcher {
private:
    std::condition_variable m_cv_queue;
    std::mutex m_cv_queue_mutex;
    std::queue<block_t> m_queue;
    std::atomic<bool> m_is_run;
    std::vector<std::thread> m_workers;
    unsigned int m_workers_count = 1;

public:
    explicit file_log(unsigned int workers_count)
            : m_is_run(true), m_workers_count(workers_count) {}

    ~file_log() override = default;

    void update(const block_t &cmd) override {
        std::unique_lock<std::mutex> lk(m_cv_queue_mutex);
        m_queue.push(cmd);
        m_cv_queue.notify_one();
    }

    void start() override {
        for (unsigned int i = 0; i < m_workers_count; ++i) {
            std::string thread_name = "file" + std::to_string(i + 1);
            meter::instance().reg_thread(thread_name);
            m_workers.emplace_back(std::thread(&file_log::worker, this, thread_name));
        }
    }

    void stop() override {
        m_is_run = false;
        m_cv_queue.notify_all();

        for (auto &wrkr : m_workers)
            wrkr.join();
    }

private:
    void dump_to_file(const block_t &cmd_block,
                      const std::string &thread_name) {
        std::ofstream output_file(get_new_filename(cmd_block.time, thread_name, cmd_block.block_seq_number));
        output_file << cmd_block.block << std::endl;
        output_file.flush();
        output_file.close();
    }

    void worker(const std::string &thread_name) {
        while (m_is_run || !m_queue.empty()) {
            std::unique_lock<std::mutex> lk(m_cv_queue_mutex);
            m_cv_queue.wait(lk, [&]() {
                return (!m_queue.empty() || !m_is_run);
            });

            if (!m_is_run && m_queue.empty())
                return;

            auto cmd_pipe = m_queue.front();
            m_queue.pop();
            lk.unlock();

            dump_to_file(cmd_pipe, thread_name);

            meter::instance().blocks_incr(thread_name);
            meter::instance().cmds_incr(thread_name, cmd_pipe.count);
        }
    }

    std::string get_new_filename(const time_t &time,
                                 const std::string &thread_name,
                                 int seq_num) {
        std::stringstream ss;
        ss << std::hex << std::this_thread::get_id();

        return "bulk" + std::to_string(time)
               + "_" + thread_name + "_"
               + std::to_string(seq_num) + "_"
               + ss.str() + ".log";
    }
};
