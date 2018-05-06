#include "handle.h"

handle::handle(unsigned int id, std::size_t bulk)
        : m_id(id)
        , m_watcher(std::make_shared<blk>(bulk))
{
    m_watcher->start_watcher();
}

handle::~handle()
{
    m_watcher->force_dump();
    m_watcher->stop_watcher();
}

unsigned int handle::id() const
{
    return m_id;
}

void handle::process_data(const char *data, std::size_t size)
{
    std::unique_lock<std::mutex> lk(m_mutex);
    m_buffer += {data, size};

    while (true) {
        auto term_pos = m_buffer.find('\n');
        if (term_pos != std::string::npos) {
            std::string cmd(m_buffer.begin(), m_buffer.begin() + term_pos);
            m_watcher->proc_cmd(cmd);
            m_buffer.erase(m_buffer.begin(), m_buffer.begin() + term_pos + 1);
        } else {
            return;
        }
    }
}

void *handle::get_raw_ptr()
{
    return static_cast<void*>(this);
}
