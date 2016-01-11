/***************************************************************
" File Name     : SNServerProc.cpp
" Author        : skytrails
" Email         : skytrails@163.com
" Create Time   : 2015-12-12 22:34
***************************************************************/

#include <errno.h>

#include "SNClientProc.h"
#include "../../pubclass/Trace.h"
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
#include <sys/socket.h>
#include <arpa/inet.h>
using namespace std;

#define SERV_PORT 9877
#define LISTENQ 1024
#define MAXLEN 256
#define MAXLINE 1024
#define SERV_PORT 9877

//初始化为守护进程
int SNCProc::init(){
    show_info("SNCProc");
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
/**
 * @brief  SNCProc:Process
 *
 * @return 
 */
int SNCProc::Process(){
  int sockfd;
  struct sockaddr_in servaddr;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(SERV_PORT);
  inet_pton(AF_INET, ptraddr, &servaddr.sin_addr);

  connect(sockfd, (struct sockaddr  *) &servaddr, sizeof(servaddr));
  str_cli(stdin, sockfd);
}

void SNCProc::str_cli(FILE *fp, int sockfd){
	show_info("");
  char sendline[MAXLINE], recvline[MAXLINE];
  while(fgets(sendline, MAXLINE, fp) != NULL){
    int ret = write(sockfd, sendline, strlen(sendline));
    if (ret == 0){
	    log_trace(1, "write empty");
    }
    if (readline(sockfd, recvline, MAXLINE) == 0){
      printf("server failed");
    }
    fputs(recvline, stdout);
  }
}


ssize_t SNCProc::readline(int fd, void *vptr, size_t maxlen){
  ssize_t n, rc;
  char c, *ptr;
  ptr = (char *)vptr;
  for(n = 1; n < maxlen; n++){
  again:
    if ((rc = read(fd, &c, 1)) == 1){
      *ptr++ = c;
      if (c == '\n'){
	break;
      }
    }
    else if(rc ==0){
      *ptr = 0;
      return (n-1);
    }
    else{
      if (errno == EINTR){
	goto again;
	return (-1);
      }
    }
  }
  *ptr = 0;
  return (n);
}

void SNCProc::setAddr(char * addr){
  ptraddr = addr;
}



