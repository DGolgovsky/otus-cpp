#pragma once

#include <ctime>
#include <string>
#include <fstream>
#include <iostream>

struct cmd_pipe_t
{
    time_t time;
    std::string cmd_pipe;
};

class observer
{
public:
    virtual void update(const cmd_pipe_t &cmd) = 0;
};

class file_logger : public observer
{
public:
    void update(const cmd_pipe_t &cmd) override {
        std::ofstream output_file(get_new_filename(cmd.time));
        output_file << cmd.cmd_pipe << std::endl;
        output_file.flush();
        output_file.close();
    }

private:
    std::string get_new_filename(const time_t &time) const {
        return "bulk" + std::to_string(time) + ".log";
    }
};

class console_logger : public observer
{
public:
    void update(const cmd_pipe_t &cmd) override {
        std::cout << "bulk: " << cmd.cmd_pipe << std::endl;
    }
};