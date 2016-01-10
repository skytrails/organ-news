/***************************************************************
" File Name     : src/business/client/client.h
" Author        : skytrails
" Email         : skytrails@163.com
" Create Time   : 2015-10-16 00:35
***************************************************************/
#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>

extern "C" int client_main(int argc, char * argv[]);
extern "C" int connect_retry(int, int, int, const struct sockaddr *, socklen_t);
void print_uptime(int sockfd);

#endif
