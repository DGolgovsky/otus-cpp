#pragma once

#include "observer.h"
#include <vector>
#include <ctime>

class storage
{
public:
    time_t time;
    std::vector<std::string> cmds;

    bool is_empty() const {
        return cmds.empty();
    }

    std::size_t commands_count() const {
        return cmds.size();
    }

    void clear() {
        cmds.clear();
    }

    void init_time() {
        time = std::time(nullptr);
        cmds.clear();
    }

    void append(const std::string &cmd) {
        cmds.push_back(cmd);
    }

    cmd_pipe_t make_pipe() {
        cmd_pipe_t pipe;
        pipe.time = time;
        for (const auto &cmd : cmds) {
            if (pipe.cmd_pipe.empty()) {
                pipe.cmd_pipe.append(cmd);
            } else {
                pipe.cmd_pipe.append(", " + cmd);
            }
        }

        return pipe;
    }
};
