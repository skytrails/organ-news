/***************************************************************
" File Name     : src/business/service/service.h
" Author        : skytrails
" Email         : skytrails@163.com
" Create Time   : 2015-10-16 00:37
***************************************************************/
#ifndef __SERVICE__H__
#define __SERVICE__H__

#define BUFLEN 128
#define MAXSLEEP 128
#define QLEN 10
#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#endif

#include <stdio.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
extern "C" int connect_retry(int, int, int, const struct sockaddr *, socklen_t);
extern "C" int service_main(int argc, char * argv[]);
void print_uptime(int sockfd);
int initserver(int type, const struct sockaddr *addr, socklen_t alen, int qlen);
void service(int sockfd);

#endif
