/***************************************************************
" File Name     : src/business/service/service.cpp
" Author        : skytrails
" Email         : skytrails@163.com
" Create Time   : 2015-10-16 00:37
***************************************************************/

#include "service.h"
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "../../pubclass/Trace.h"
#include "../../util/deamon/deamon.h"

#define BUFLEN 128
int service_main(int argc, char * argv[]){
	show_info("");
    struct addrinfo *ailist, *aip;
    struct addrinfo hint;
    int sockfd, err, n;
    char *host;

    if (argc != 1){
        log_trace(1, "usage: ruptimed");
    }
    if ((n = sysconf(_SC_HOST_NAME_MAX)) < 0){
        n = HOST_NAME_MAX;
    }
    if ((host = (char*)malloc(n)) == NULL){
        log_trace(1, "malloc error");
    }
    if (gethostname(host, n) < 0){
        log_trace(1, "get host name error");
    }
    log_trace(1, "begin, hostname:%s", host);
    deamonize("ruptimed");
    log_trace(1, "1end");
    memset(&hint, 0, sizeof(hint));
    hint.ai_flags = AI_CANONIDN;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_canonname = NULL;
    hint.ai_addr = NULL;
    hint.ai_next = NULL;
    if ((err = getaddrinfo(host, "service", &hint, &ailist)) != 0){
        log_trace(1, "ruptimed: getaddrinfo error: %s", gai_strerror(err));
    }
    for (aip = ailist; aip != NULL; aip = aip->ai_next){
        if ((sockfd = initserver(SOCK_STREAM, aip->ai_addr, aip->ai_addrlen, QLEN)) >= 0){
            service(sockfd);
            exit(0);
        }
    }

    log_trace(1, "end");
    return 0;
}


void service(int sockfd){
	show_info("");
    int clfd;
    FILE *fp;
    char buf[BUFLEN];
    set_cloexec(sockfd);
    for (;;){
        if ((clfd = accept(sockfd, NULL, NULL)) < 0){
            log_trace(1, "ruptimed: accept error: %s", strerror(errno));
            exit(1);
        }
        set_cloexec(clfd);
        log_trace(1, "service popen");
        if ((fp = popen("/usr/bin/uptime", "r")) == NULL){
            log_trace(1, "NULL == service popen");
            sprintf(buf, "error: %s\n", strerror(errno));
            send(clfd, buf, strlen(buf), 0);
        }
        else{
            log_trace(1, "NULL != service popen:");
            while (fgets(buf, BUFLEN, fp) != NULL){
            log_trace(1, " while :%s", buf);
                send(clfd, buf, strlen(buf), 0);
            }
            pclose(fp);
        }
    }
}

int initserver(int type, const struct sockaddr *addr, socklen_t alen, int qlen){
    int fd;
    int err = 0;
    if ((fd = socket(addr->sa_family, type, 0)) < 0){
        return -1;
    }
    if (bind(fd, addr, alen) < 0){
        goto errout;
    }
    if (type == SOCK_STREAM || type == SOCK_SEQPACKET){
        if (listen(fd, qlen) < 0)
            goto errout;
    }
    return fd;

errout:
    err = errno;
    close(fd);
    errno = err;
    return -1;
}
