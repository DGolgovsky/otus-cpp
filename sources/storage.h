#pragma  once

#include "handle.h"

#include <mutex>
#include <map>

class storage
{
public:
    static storage &instance() {
        static storage inst;
        return inst;
    }

    void* create(std::size_t bulk) {
        std::unique_lock<std::mutex> lk(m_mutex);
        auto storage = std::make_shared<handle>(m_id, bulk);
        m_handles.insert(std::make_pair(m_id, storage));
        ++m_id;
        return storage->get_raw_ptr();
    }

    void destroy(unsigned int id) {
        std::unique_lock<std::mutex> lk(m_mutex);
        auto it = m_handles.find(id);
        if (it != m_handles.end())
            m_handles.erase(it);
    }

    storage(const storage&) = delete;
    storage& operator=(const storage&) = delete;

private:
    storage() = default;

    std::map<unsigned int, std::shared_ptr<handle>> m_handles;
    unsigned int m_id = 0;
    std::mutex m_mutex;
};
