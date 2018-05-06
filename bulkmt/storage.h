#pragma once

#include <vector>
#include <ctime>

struct storage_t
{
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

    void add(std::string const &cmd) {
        cmds.push_back(cmd);
    }

    block_t make_block(int seq_num) {
        block_t cmd_block;
        cmd_block.time = time;
        cmd_block.count = cmds.size();
        cmd_block.block_seq_number = seq_num;

        for (auto const &cmd : cmds) {
            if (cmd_block.block.empty()) {
                cmd_block.block.append(cmd);
            } else {
                cmd_block.block.append(", " + cmd);
            }
        }

        return cmd_block;
    }
};
