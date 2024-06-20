#include "ExternalCommand.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cerrno>
#include <cstring>

void ExternalCommand::execute() {
    pid_t pid = fork();
    if (pid == 0) {//子进程并进行进程替换执行对应命令
        std::vector<char*> c_args;
        for (const auto& arg : args) {
            c_args.push_back(const_cast<char*>(arg.c_str()));
        }
        c_args.push_back(nullptr);//execvp 末尾必须以nullptr结尾

        execvp(c_args[0], c_args.data()); //传入程序名称和对应参数列表
        std::cerr << "execvp: " << std::strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    } else if (pid > 0) {//父进程等待子进程进行资源回收
        wait(nullptr);
    } else {//差错处理
        std::cerr << "fork: " << std::strerror(errno) << std::endl;
    }
}
 