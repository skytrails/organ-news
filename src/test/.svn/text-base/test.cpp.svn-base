/***************************************************************
" File Name     : test.cpp
" Author        : skytrails
" Email         : skytrails@163.com
" Create Time   : 2015-09-21 23:43
***************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <wchar.h>
#include "../pubclass/Trace.h"
#include <arpa/inet.h>
#include <unistd.h>
#include "../util/util.h"
#define MAXLEN 256
/*
int main(int argc, char *argv[]){
    int sockfd, n;
    char recvline[256];
    struct sockaddr_in servaddr;
    if (argc < 2){
        log_trace(1, "usage: tst <IPaddress>");
        exit(-1);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0){
        log_trace(1, "call socket failed!");
    }
    log_trace(1, "sockfd:%d", sockfd);
    bzero(&servaddr , sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = 4000;//htons(13);
    log_trace(1, "servaddr.sin_port:%d", htons(13));
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0){
        log_trace(1, "inet_pton error for %s", argv[1]);
    }
    if (connect(sockfd, ( sockaddr *) &servaddr, sizeof(servaddr)) < 0){
        log_trace(1, "connect error");
    }
    while((n = read(sockfd, recvline, MAXLEN)) > 0){
        recvline[n] = 0;
        if (fputs(recvline, stdout) == EOF){
            log_trace(1, "fputs error");
        }
    }
    return 0;
}
*/

void show_pton();
void show_ntop();

int test_main(int argc, char * argv[]){
    Z_Daemonize("tst");
    return 0;
}

void show_pton(){
    log_trace(1, "begin show_pton");
    struct in_addr addr;
    inet_pton(AF_INET, "10.75.152.18", &addr);
    show_binary(addr.s_addr);
    show_binary(10);
    show_binary(75);
    show_binary(152);
    show_binary(18);
}

void show_ntop(){
    log_trace(1, "begin show_ntop");
}
