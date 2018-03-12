#include "writer.h"
#include <ctime>

class Bulk
{
public:
    explicit Bulk(std::size_t _n);
    ~Bulk();
    void read_cmds(std::string);
    void write_cmds();

private:
    std::vector<std::string> bulk;
    std::vector<char> brackets;
    std::string timestamp = "";
    bool first_cmd = true;
    std::size_t n;

    Writer *console_wrtr = nullptr;
    Writer *file_wrtr = nullptr;
};
