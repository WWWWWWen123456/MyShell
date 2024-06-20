//普通命令 比如ls -a -i -l 
#ifndef EXTERNALCOMMAND_H
#define EXTERNALCOMMAND_H

#include "Command.h"

class ExternalCommand : public Command {
public:
    ExternalCommand(const std::vector<std::string>& args) : Command(args) {}
    void execute() override;
};

#endif // EXTERNALCOMMAND_H
 