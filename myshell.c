// shell 运行原理 ： 通过让子进程执行命令，父进程等待&&解析命令
#include"myshell.h"

int main()
{
    extern char**environ;
    //0. 命令行解释器，一定是一个常驻内存的进程，不退出
    while(1)
    {
        //1. 打印出提示信息
        printf("[root@localhost myshell]# ");
        fflush(stdout);
        memset(cmd_line, '\0', sizeof cmd_line);
        //2. 获取用户的键盘输入[输入的是各种指令和选项: "ls -a -l -i"]
        if(fgets(cmd_line, sizeof cmd_line, stdin) == NULL)
        {
            continue;
        }
        cmd_line[strlen(cmd_line)-1] = '\0';
        //"ls -a -l -i\n\0"
        //printf("echo: %s\n", cmd_line);
        //3. 命令行字符串解析："ls -a -l -i" -> "ls" "-a" "-i"
        // export myval=105
        g_argv[0] = strtok(cmd_line, SEP); //第一次调用，要传入原始字符串
        int index = 1;
        if(strcmp(g_argv[0], "ls") == 0)
        {
            g_argv[index++] = "--color=auto";
        }
        if(strcmp(g_argv[0], "ll") == 0)
        {
            g_argv[0] = "ls";
            g_argv[index++] = "-l";
            g_argv[index++] = "--color=auto";
        }
        //?
        while(g_argv[index++] = strtok(NULL, SEP)); //第二次，如果还要解析原始字符串,传入NULL
        if(strcmp(g_argv[0], "export") == 0 && g_argv[1] != NULL)
        {
            strcpy(g_myval, g_argv[1]);
            int ret = putenv(g_myval);
            if(ret == 0) printf("%s export success\n", g_argv[1]);
            //for(int i = 0; environ[i]; i++)
            //    printf("%d: %s\n", i, environ[i]);
            continue;
        }

        //for debug
        //for(index = 0; g_argv[index]; index++)
        //    printf("g_argv[%d]: %s\n", index, g_argv[index]);
        //4.内置命令, 让父进程（shell）自己执行的命令，我们叫做内置命令，内建命令
        //内建命令本质其实就是shell中的一个函数调用
        if(strcmp(g_argv[0], "cd") == 0) //not child execute, father execute
        {
            if(g_argv[1] != NULL) chdir(g_argv[1]); //cd path, cd ..

            continue;
        }
        //5. fork()
        pid_t id = fork();
        if(id == 0) //child
        {
            printf("下面功能让子进程进行的\n");
            printf("child, MYVAL: %s\n", getenv("MYVAL"));
            printf("child, PATH: %s\n", getenv("PATH"));
            //cd cmd , current child path
            //execvpe(g_argv[0], g_argv, environ); // ls -a -l -i
            //不是说好的程序替换会替换代码和数据吗？？
            //环境变量相关的数据，会被替换吗？？没有！
            execvp(g_argv[0], g_argv); // ls -a -l -i
            exit(1);
        }
        //father
        int status = 0;
        pid_t ret = waitpid(id, &status, 0);
        if(ret > 0) printf("exit code: %d\n", WEXITSTATUS(status));
    }
}
