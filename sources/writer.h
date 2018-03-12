#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <fstream>


class Writer
{
public:
    virtual void write(std::vector<std::string> &) = 0;
    virtual ~Writer() = default;
};

class ConsoleWriter : public Writer
{
public:
    void write(std::vector<std::string> &) override;
};

class FileWriter : public Writer
{
public:
    void write(std::vector<std::string> &) override;
    void set_timestamp(std::string);

private:
    std::string timestamp;
};
