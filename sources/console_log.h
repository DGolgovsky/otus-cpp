#pragma once

#include <iostream>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <thread>
#include <queue>

class console_log : public watcher
{
private:
    std::condition_variable m_cv_queue;
    std::mutex m_cv_queue_mutex;
    std::queue<block_t> m_queue;
    std::atomic<bool> m_is_run;
    std::thread m_worker;

    std::string m_thread_name = "log";

public:
    console_log()
            : m_is_run(true)
    {
        meter::instance().reg_thread(m_thread_name);
    }

    ~console_log() override = default;

    void update(const block_t &cmd) override {
        std::unique_lock<std::mutex> lk(m_cv_queue_mutex);
        m_queue.push(cmd);
        m_cv_queue.notify_one();
    }

    void start() override {
        m_worker = std::thread(&console_log::worker, this);
    }

    void stop() override {
        m_is_run = false;
        m_cv_queue.notify_all();

        m_worker.join();
    }

private:
    void worker() {
        while (m_is_run || !m_queue.empty()) {
            std::unique_lock<std::mutex> lk(m_cv_queue_mutex);
            m_cv_queue.wait(lk, [&] () {
                return (!m_queue.empty() || !m_is_run);
            });

            if (!m_is_run && m_queue.empty())
                return;

            auto cmd_pipe = m_queue.front();
            m_queue.pop();
            lk.unlock();

            std::cout << "bulk: " << cmd_pipe.block << std::endl;

            meter::instance().blocks_incr(m_thread_name);
            meter::instance().cmds_incr(m_thread_name, cmd_pipe.count);
        }
    }
};
