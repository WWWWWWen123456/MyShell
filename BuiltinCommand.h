// 处理内置命令类的头文件和声名
#ifndef BUILTINCOMMAND_H
#define BUILTINCOMMAND_H

#include "Command.h"

class BuiltinCommand : public Command { 
public:
    BuiltinCommand(const std::vector<std::string>& args) : Command(args) {}
    void execute() override;
};

#endif // BUILTINCOMMAND_H
