#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <tuple>

#include <boost/lexical_cast.hpp>

using Commands = std::vector<std::tuple<time_t, std::string>>;

class Processor
{
public:

    virtual void process(const Commands&) = 0;
};
using Processors = std::vector<Processor*>;

class ProcessorSubscriber
{
private:
    Processors _processors;

public:

    void process(const Commands& commands)
    {
        for(auto p : _processors)
            p->process(commands);
    }

    void subscribe(Processor* processor)
    {
        _processors.push_back(processor);
    }
};

class ConsolePrint : public Processor
{
private:
    std::ostream& _out;

public:
    ConsolePrint(ProcessorSubscriber& ps, std::ostream& out = std::cout) : _out(out)
    {
        ps.subscribe(this);
    }

    virtual void process(const Commands& commands) final {
        if(commands.size() == 0)
            return;

        _out << "bulk: ";
        bool first = true;
        for(auto c :commands)
        {
            if(first)
                first = false;
            else
                _out << ", ";
            _out << std::get<1>(c);
        }
        _out << std::endl;
    }
};

class IFileWriter
{
public:
    virtual void open(const std::string& name) = 0;
    virtual std::ostream& out() = 0;
    virtual void close() = 0;
};

class FileWriter : public IFileWriter
{
private:
    std::ofstream _out;

public:
    virtual void open(const std::string& name) final {
        _out.open(name, std::ios::app);
    }
    virtual std::ostream& out() final {
        return _out;
    }
    virtual void close() final {
        _out.close();
    }
};

class FilePrint : public Processor
{
private:
    IFileWriter* _file_writer;

public:
    FilePrint(ProcessorSubscriber& ps, IFileWriter* file_writer = new FileWriter) : _file_writer(file_writer)
    {
        ps.subscribe(this);
    }
    ~FilePrint()
    {
        delete _file_writer;
    }

    virtual void process(const Commands& commands) final {
        if(commands.size() == 0)
            return;

        std::string name = "bulk";
        name += boost::lexical_cast<std::string>(std::get<0>(*(commands.begin())));
        name += ".log";

        _file_writer->open(name);
        for(auto c :commands)
            _file_writer->out() << std::get<1>(c) << std::endl;
        _file_writer->close();
    }
};

class ITime
{
public:
    virtual time_t get() = 0;
};

class Time : public ITime
{
public:
    virtual time_t get() final {
        return std::time(nullptr);
    };
};

class Reader : public ProcessorSubscriber
{
private:
    ITime* _time;

    size_t _N;

    void flush(Commands& commands)
    {
        if(commands.size() > 0) {
            process(commands);
            commands.clear();
        }
    }

public:
    Reader(size_t N = 0, ITime* time = new Time) : _time(time), _N(N) {}
    ~Reader()
    {
        delete _time;
    }

    void read(std::istream& in)
    {
        Commands commands;
        size_t bracket_counter = 0;
        std::string line;
        while(std::getline(in, line)) {
            if(line == "{") {
                if(bracket_counter++ == 0)
                    flush(commands);
            } else if(line == "}") {
                if(bracket_counter > 0 && --bracket_counter == 0)
                    flush(commands);
            } else {
                commands.push_back(std::make_tuple(_time->get(), line));
                if(bracket_counter == 0 && _N != 0 && commands.size() == _N)
                    flush(commands);
            }
        }
        if(bracket_counter == 0)
            flush(commands);
    }
};
