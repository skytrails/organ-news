/***************************************************************
" File Name     : process.cpp
" Author        : skytrails
" Email         : skytrails@163.com
" Create Time   : 2015-09-19 22:31
***************************************************************/

#include "process.h"
#include "unistd.h"
#include <stdio.h>
#include <stdlib.h>
#include "sys/wait.h"
#include "Trace.h"

CProcess::CProcess(){
    //TODO ADD CODE
}

CProcess::~CProcess(){
    //TODO ADD CODE
}

int CProcess::init(){
    show_info();
    pid_t pid;
    pid = fork();
    if (pid < 0){
        log_trace(1, "call fork failed");
        return 0;
    }
    else if (pid == 0){
        // 关闭标准流
        chdir("/");
#ifndef _DEBUG
        close(STDOUT_FILENO);
        close(STDIN_FILENO);
        close(STDERR_FILENO);
#endif
    }
    else{
        exit(0);
    }
    return 1;   // 返回1表示调用成功
}

int CProcess::process(){
    show_info();
    while(1);
    return 1;
}
