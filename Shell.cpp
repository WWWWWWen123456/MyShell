#include "Shell.h"
#include <iostream>
#include <sstream> 
#include <fstream>
#include "BuiltinCommand.h"
#include "ExternalCommand.h"

void Shell::run() {
    while (true) {//常驻内存的进程 死循环
        print_prompt();
        //从键盘上获取对应的命令并且处理 
        std::string input = get_input();
        if (input.empty()) continue;

        std::vector<std::string> args = parse_command(input);
        if (args.empty()) continue;

        if (args[0] == "exit") break;

        handle_command(args);
    }
}

void Shell::execute_script(const std::string &script_file) {
    std::ifstream script(script_file);
    if (!script) {
        std::cerr << "Could not open script file: " << script_file << std::endl;
        return; //打开文件流
    }
    //将文件内容逐行读取并且存储解析处理
    std::string line;
    while (std::getline(script, line)) {
        std::vector<std::string> args = parse_command(line);
        if (args.empty()) continue;

        if (args[0] == "exit") break;

        handle_command(args);
    }

    script.close(); // 关闭文件流
    return;

}
//打印命令行提示符 注意及时刷新 否则显示有问题
void Shell::print_prompt() {
    std::cout << "[root@localhost myshell]# ";
    std::cout.flush();
}
//读取键盘输入并且构造对应的字符串
std::string Shell::get_input() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}
//拆分命令 进行解析 ls -a -l 
std::vector<std::string> Shell::parse_command(const std::string &input) {
    std::vector<std::string> args;
    std::istringstream tokenStream(input);
    std::string token;
    while (tokenStream >> token) {//重定向到token中
        args.push_back(token);
    }
    return args;
}
//判断命令的类型并且进行处理
void Shell::handle_command(const std::vector<std::string> &args) {
    Command* cmd;
    //处理内置命令
    if (args[0] == "cd" || args[0] == "export") {
        cmd = new BuiltinCommand(args);
    } else {//处理一般命令
        cmd = new ExternalCommand(args);
    }

    cmd->execute();
    delete cmd;
}
