/***************************************************************
" File Name     : SNServerProc.h
" Author        : skytrails
" Email         : skytrails@163.com
" Create Time   : 2015-12-12 22:35
***************************************************************/

#ifndef _SN_CLIENT_PROC__
#define _SN_CLIENT_PROC_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../pubclass/argOptionsMgr.h"

class SNCProc{
public:
    SNCProc(){
        char * pDebug = getenv("DEBUG");
        _debug = false;
        if (pDebug && strcmp(pDebug, "true") == 0){
            _debug = true;
        }
    };
public:
    int init();
    int Process();
    void str_cli(FILE *fp, int sockfd);
    ssize_t readline(int fd, void *vptr, size_t maxlen);
    void setAddr(char * addr);
public:
    bool _debug;
    char * ptraddr;
    int argc_t;

};




#endif



