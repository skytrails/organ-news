/***************************************************************
" File Name     : SNServerProc.cpp
" Author        : skytrails
" Email         : skytrails@163.com
" Create Time   : 2015-12-12 22:34
***************************************************************/

#include "SNServerProc.h"
#include "pubclass/Trace.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fstream>
#include <iostream>
#include <syslog.h>
#include <sys/resource.h>
#include <time.h>
#include <signal.h>
#include <netinet/in.h>
#include <string.h>
using namespace std;

#define SERV_PORT 9877
#define LISTENQ 1024
#define MAXLEN 256
#define MAXLINE 1024


//初始化为守护进程
int SNSProc::init(){
    show_info();
    pid_t pid;
    pid = fork();
    if (pid < 0){
        log_trace(1, "SNSProc init failed");
        return 0;
    }
    else if (pid > 0){
        exit(0);
    }

    umask(0);
    char *logfile = getenv("SNS_LOG_FILE");
    if (logfile != NULL){
        ofstream fout(logfile);
        if (!fout) exit(-1);
    }

    pid_t sid;
    sid = setsid();
    if (sid < 0){
        exit(-1);
    }


    if ((chdir("/")) < 0){
        exit(-1);
    }
    if (!_debug){
    close(STDOUT_FILENO);
    close(STDIN_FILENO);
    close(STDERR_FILENO);
    }

    return 1;
}
int SNSProc::SNSProcess(){
    int listenfd, connfd;
    struct sockaddr_in cliaddr, servaddr;
    socklen_t clilen;
    pid_t childpid;
    log_trace(1, "SNSProcess begin");
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    //bzero(&servaddr, (const struct sockaddr*)&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    bind(listenfd, (const struct sockaddr*) &servaddr, sizeof(servaddr));
    listen(listenfd, LISTENQ);
    
    while(1){
        clilen = sizeof(cliaddr);
        log_trace(1, "accept befor");
        connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &clilen);
        log_trace(1, "accept after");
        if ((childpid = fork()) == 0) {
            close(listenfd);
            _read(connfd);
            exit(0);
        }
        close(connfd);
    }
}

int SNSProc::_read(int sockfd){
    ssize_t n;
    char buf[MAXLEN];
again:
    while((n = read(sockfd, buf, MAXLINE)) > 0){
        write(sockfd, buf, n);

        if (n < 0){
            printf("error");
        }
    }
}
