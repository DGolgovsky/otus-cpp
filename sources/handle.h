#include <memory>
#include <mutex>
#include <algorithm>

#include <blk.h> // class bulk

class handle
{
public:
    handle(unsigned int id, std::size_t bulk);
    ~handle();
    unsigned int id() const;
    void process_data(const char *data, std::size_t size);
    void *get_raw_ptr();

private:
    unsigned int m_id;
    std::string m_buffer;
    std::shared_ptr<blk> m_watcher;
    std::mutex m_mutex;
};
