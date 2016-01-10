/***************************************************************
" File Name     : deamon.cpp
" Author        : skytrails
" Email         : skytrails@163.com
" Create Time   : 2015-09-08 08:13
***************************************************************/
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include "deamon.h"
#include <syslog.h>
#include <sys/resource.h>
#include "../../pubclass/Trace.h"

using namespace std;

int func(){
    printf("fanyi");
    return 1;
}
    pid_t pid, sid;

int z_deamon() {

    pid_t pid, sid;

    // Fork off the parent process
    pid = fork();
    if (pid < 0){
        exit(-1);
    }

    // If we got a good PID, then we can exit the parent process.
    if (pid > 0) {
        exit(-1);
    }

    // Change the file mode mask
    umask(0);

    // Open any logs here
    ofstream fout("/home/skytrails/log/deamon.log");
    if (!fout){ 
        exit(-1);
    }

    // Create a new SID(Session ID) for the child process.
    sid = setsid();
    if (sid < 0){
        // Log any failure
        exit(-1);
    }

    // Change the current working directory
    if ((chdir("/")) < 0){
        // Log any failure
        exit(-1);
    }

    // close out the standard file descriptors
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // Daemon-specific initialization goes here
    
    // The big loop
    while(true){
        time_t timeNow;
        time(&timeNow);
        fout << asctime(localtime(&timeNow)) << endl;

        sleep(30);
    }
    cout << "over" << endl;
    return 0;
}

//守护进程
extern "C" void deamonize(const char *cmd){
    int i, fd0, fd1, fd2;
    pid_t pid;
    struct rlimit rl;
    struct sigaction sa;
    if (getrlimit(RLIMIT_NOFILE, &rl) < 0){
        log_trace(1, "%s: can't get file limit", cmd);
    }
    if ((pid = fork()) < 0){
        log_trace(1, "%s: can't fork", cmd);
    }
    else if (pid != 0){
        exit(0);
    }
    setsid();
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) < 0){
        log_trace(1, "%s: can't ignore SIGHUP", cmd);
    }
    if ((pid = fork()) < 0){
        log_trace(1, "%s: can't fork", cmd);
    }
    else if(pid != 0){
        exit(0);
    }
    if (chdir("/") < 0){
        log_trace(1, "%s: can't change dir", cmd);
    }

    if (rl.rlim_max == RLIM_INFINITY){
        rl.rlim_max = 1024;
    }
    for (i = 0; i < rl.rlim_max; i++){
        close(i);
    }
    //fd0 = open("/dev/null", O_RDWR);
    fd0 = open("/home/skytrails/back_trunk/service.log", O_RDWR);
    fd1 = dup(fd0);
    fd2 = dup(fd0);

    openlog(cmd, LOG_CONS, LOG_DAEMON);
    if (fd0 != 0 || fd1 != 1 || fd2 != 2) {
        syslog(LOG_ERR, "unexpected file descriptors %d %d %d", fd0, fd1, fd2);
        exit(1);
    }
}

int set_cloexec(int fd){
    int val;
    if ((val = fcntl(fd, F_GETFD, 0)) < 0){
        return -1;
    }
    val |= FD_CLOEXEC;
    return (fcntl(fd, F_SETFD, val));
}
