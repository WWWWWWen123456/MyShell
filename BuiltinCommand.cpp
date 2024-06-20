//处理cd和export内置命令
#include "BuiltinCommand.h"
#include <iostream>
#include <unistd.h>
#include <cstdlib> 
#include <cerrno>
#include <cstring>

void BuiltinCommand::execute() {
    //一般是cd +路径 比如：cd /home/usr/.. 因此是两个参数
    if (args[0] == "cd") {
        if (args.size() > 1) {//chdir进程替换切换进程以及对应差错处理
            if (chdir(args[1].c_str()) != 0) {
                std::cerr << "cd: " << std::strerror(errno) << std::endl;
            }
        } else {//差错处理
            std::cerr << "cd: missing argument" << std::endl;
        }//export PATH=/usr/local/bin:$PATH
    } else if (args[0] == "export") { 
        if (args.size() > 1) {
            std::string var = args[1];
            size_t eq_pos = var.find('=');//分割 
            if (eq_pos != std::string::npos) {
                std::string name = var.substr(0, eq_pos);//变量名称
                std::string value = var.substr(eq_pos + 1);//变量值
                setenv(name.c_str(), value.c_str(), 1);//设置环境变量
            } else {
                std::cerr << "export: invalid format" << std::endl;
            }
        } else {
            std::cerr << "export: missing argument" << std::endl;
        }
    }
}
