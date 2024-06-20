//shell的头文件和声名
#ifndef SHELL_H
#define SHELL_H

#include <string>
#include <vector>
#include "Command.h" 

class Shell {
public:
    void run();
    void execute_script(const std::string &script_file);

private:
    void print_prompt();
    std::string get_input();
    std::vector<std::string> parse_command(const std::string &input);
    void handle_command(const std::vector<std::string> &args);
};

#endif // SHELL_H
