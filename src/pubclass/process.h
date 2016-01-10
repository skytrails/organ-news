/***************************************************************
" File Name     : process.h
" Author        : skytrails
" Email         : skytrails@163.com
" Create Time   : 2015-09-19 22:31
***************************************************************/

#ifndef _C_PROCESS_H_
#define _C_PROCESS_H_

class CProcess{
public:
    CProcess();
    ~CProcess();
public:
    int init();
    virtual int process();
};

#endif
