#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define NUM 1024
#define SIZE 32
#define SEP " "

//保存完整的命令行字符串
char cmd_line[NUM];

//保存打散之后的命令行字符串
char *g_argv[SIZE];

// 写一个环境变量的buffer，用来测试
char g_myval[64];

