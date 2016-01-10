/***************************************************************
" File Name     : util.cpp
" Author        : skytrails
" Email         : skytrails@163.com
" Create Time   : 2015-11-01 20:46
***************************************************************/
#include "util.h"

#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <syslog.h>
#include <signal.h>

int show_binary(int src){
    int i = 0;
    int tmp = src;
    int bn = 8 * sizeof(src);
    for (i = 0; i < bn; ++i){
        //std::cout << ((tmp >> bn - i - 1) & 1);
        printf("%d", ((tmp >> bn - i - 1) & 1));
    }
    printf("\n");
    return 0;
}

//int show_binary(double src){
//    std::cout << "double to binary no suppert now" << std::endl;
//}
/*
 * 守护进程初始化函数
 */
extern "C" int Z_Daemonize(const char * cmd){
    int i ;
    int fd0, fd1, fd2;
    struct rlimit rl;
    struct sigaction sa;
    umask(0);
    pid_t pid;
    /*
     * Get maxinum number of file descriptors
     */
    if (getrlimit(RLIMIT_NOFILE, &rl) < 0){
        printf("cant't get file limit");
        exit(1);
    }

    if ((pid = fork()) > 0){
        exit(0);
    }
    else if (pid < 0){ 
        printf(" fork failed");
    }

    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) < 0){
        printf("can't ignore SIGHUP");
    }
    if ((pid = fork()) < 0){
        printf("fork failed");
        exit(1);
    }
    else if (pid > 0){
        exit(0);
    }

    if (chdir("/")){
        printf("chdir failed");
        exit(1);
    }
    if (rl.rlim_max == RLIM_INFINITY){
        rl.rlim_max = 1024;
    }
    for (i = 0; i < rl.rlim_max; i++){
        close(i);
    }
    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);

    openlog(cmd, LOG_CONS, LOG_DAEMON);
    if (fd0 != 0 || fd1 != 1 || fd2 != 2){
        syslog(LOG_ERR, "unexpected fle descriptors %d %d %d", fd0, fd1, fd2);
        exit(1);
    }
    syslog(LOG_ERR, "fadf");
}

/*void err_quit(const char *fmt, ...){

    va_list ap;
    va_start(ap, fmt);
    err_doit(0, 0, fmt, ap);
    va_end(ap);
    exit(1);
}
*/
