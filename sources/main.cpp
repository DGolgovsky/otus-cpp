#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

//#define DEBUG

struct Commands
{
    std::vector<std::string> cmds;
    time_t timestamp{};
    int cmdCounter{};

    void push_back(const std::string &str) {
        if (cmds.empty())
            timestamp = time(nullptr);

        cmds.push_back(str);
        ++cmdCounter;
    }

    void push_back_block(const std::string &str) {
        if (cmds.empty())
            timestamp = time(nullptr);

        cmds.push_back(str);
    }

    void clear() {
        cmds.clear();
        cmdCounter = 0;
    }
};

class Observer
{
public:
    virtual void dump(Commands const &cmd) = 0;
};

class Dumper
{
private:
    Commands cmds;
    std::vector<Observer *> subs;

public:
    void subscribe(Observer *rhs) noexcept {
        subs.push_back(rhs);
    }

    void notify() const noexcept {
        for (auto const &s : subs)
            s->dump(cmds);
    }

    void dump_commands(Commands &cmd) noexcept {
        cmds = cmd;
        notify();
    }
};

class ConsoleDumper : public Observer
{
public:
    explicit ConsoleDumper(Dumper *dmp) {
        dmp->subscribe(this);
    }

    void dump(Commands const &cmd) override {
        bool is_first = true;
        std::cout << "bulk: ";

        for (const auto &s : cmd.cmds) {
            if (!is_first) {
                std::cout << ", ";
            } else {
                is_first = false;
            }
            std::cout << s;
        }
        std::cout << std::endl;
    }
};

class FileDumper : public Observer
{
public:
    explicit FileDumper(Dumper *dmp)
    {
        dmp->subscribe(this);
    }

    void dump(Commands const &cmd) override {
        std::string filename = "bulk" + std::to_string(cmd.timestamp) + ".log";
        std::ofstream of(filename);

        bool is_first = true;
        of << "bulk: ";
        for (const auto &s : cmd.cmds) {
            if (!is_first) {
                of << ", ";
            } else {
                is_first = false;
            }
            of << s;
        }
        of << std::endl;
        of.close();
    }
};

int main(int argc, char const **argv)
{
#ifdef DEBUG
    freopen("cmd_input.txt", "rt", stdin);
#endif

    int cnt_cmds = 0;
    if (argc > 1) {
        cnt_cmds = atoi(*argv);
    } else {
        std::cerr << "Bad input" << std::endl;
        return 0;
    }

    Dumper dumper;
    ConsoleDumper console_dmp(&dumper);
    FileDumper file_dmp(&dumper);
    Commands cmds;

    std::string line;
    int nestedBlocksCount = 0;
    bool blockFound = false;

    while (getline(std::cin, line)) {
        if (line != "{" && !blockFound) {
            cmds.push_back(line);

            if (cmds.cmdCounter != cnt_cmds) continue;
            dumper.dump_commands(cmds);
            cmds.clear();
        } else if (blockFound) {
            if (line == "{") {
                ++nestedBlocksCount;
            } else if (line == "}") {
                if (nestedBlocksCount <= 0) {
                    dumper.dump_commands(cmds);
                    cmds.clear();
                    blockFound = false;
                } else {
                    --nestedBlocksCount;
                }
            } else {
                cmds.push_back_block(line);
            }
        } else {
            blockFound = true;
            if (!cmds.cmdCounter) continue;
            dumper.dump_commands(cmds);
            cmds.clear();
        }
    }

    if(cmds.cmdCounter) {
        dumper.dump_commands(cmds);
    }

    return 0;
}
