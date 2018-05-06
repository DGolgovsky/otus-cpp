#pragma once

#include <ctime>
#include <string>

struct block_t
{
    time_t time;
    std::string block;
    unsigned long count;
    unsigned int block_seq_number;
};

class watcher
{
public:
    virtual void update(const block_t &cmd) = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual ~watcher() = default;
};
