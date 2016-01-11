/***************************************************************
" File Name     : src/business/client/client.cpp
" Author        : skytrails
" Email         : skytrails@163.com
" Create Time   : 2015-10-16 00:35
***************************************************************/
#define BUFLEN 128
#define MAXSLEEP 28
#include "client.h"
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>
#include "../../pubclass/Trace.h"
#include "../../pubclass/argOptionsMgr.h"
int client_main(int argc, char * argv[]){
    show_info("");
    struct addrinfo *ailist, *aip;
    struct addrinfo hint;
    int sockfd, err;

    if (argc != 2){
        log_trace(1, "usage: reptime hostname");
    }
    memset(&hint, 0, sizeof(hint));
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_canonname = NULL;
    hint.ai_addr = NULL;
    hint.ai_next = NULL;
    //if ((err = getaddrinfo(argv[1], "service", &hint, &ailist)) != 0)
    if ((err = getaddrinfo("debian", "service", &hint, &ailist)) != 0)
        log_trace(1, "getaddrinfo error: %s", gai_strerror(err));
    
    for (aip = ailist; aip != NULL; aip = aip->ai_next) {
            log_trace(1, "1aip--recv success?:%l-----", atol(aip->ai_addr->sa_data));
        if ((sockfd = connect_retry(aip->ai_family, SOCK_STREAM, 0, \
                        aip->ai_addr, aip->ai_addrlen)) < 0) {
            log_trace(1, "7aip--recv success?");
            err = errno;
        }
        else{
            log_trace(1, "2aip--recv success?:%d");
            print_uptime(sockfd);
            _exit(0);
        }
    }
    log_trace(1, "can't connect to %s", argv[1]);
    exit(0);
}


void print_uptime(int sockfd){
	show_info("");
    int n;
    char buf[BUFLEN];

    while((n = recv(sockfd, buf, BUFLEN, 0))> 0){
        int ret = write(STDOUT_FILENO, buf, n);
	if (ret <= 0){
		return;
	}
    }
    log_trace(1, "recv success?");
    if (n < 0)
        log_trace(1, "recv error");
}

int connect_retry(int domain, int type, int protocol, const struct sockaddr *addr, socklen_t alen){
	show_info("");
    int numsec, fd;
    for (numsec = 1; numsec <= MAXSLEEP; numsec <<= 1){
        if ((fd = socket(domain, type, protocol)) < 0)
            return (-1);
        if (addr->sa_data == NULL){
            log_trace(1, "NULL");
        }
        log_trace(1, "addr:%l", atol(addr->sa_data));
        char t[15];
        inet_ntop(AF_INET, addr, t, 16);
        log_trace(1, "addr:%s", t);
        if (connect(fd, addr, alen) == 0) {
            return fd;
        }
        close(fd);
        if (numsec <= MAXSLEEP/2){
            sleep(numsec);
        }
    }
    return -1;
}
