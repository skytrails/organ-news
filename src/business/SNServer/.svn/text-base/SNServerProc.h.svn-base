/***************************************************************
" File Name     : SNServerProc.h
" Author        : skytrails
" Email         : skytrails@163.com
" Create Time   : 2015-12-12 22:35
***************************************************************/

#ifndef _SNS_SERVER_PROC_
#define _SNS_SERVER_PROC_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

class SNSProc{
public:
    SNSProc(){
        char * pDebug = getenv("DEBUG");
        _debug = false;
        if (pDebug && strcmp(pDebug, "true") == 0){
            _debug = true;
        }
    };
public:
    int init();
    int SNSProcess();
    int _read(int sockfd);

public:
    bool _debug;


};
#endif
