#ifndef COMMAND_H
#define COMMAND_H

#include <vector>
#include <string>

class Command { 
public:
    virtual ~Command() {}
    virtual void execute() = 0;

protected:
    Command(const std::vector<std::string>& args) : args(args) {}
    std::vector<std::string> args;
};

#endif // COMMAND_H
