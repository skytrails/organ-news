/***************************************************************
" File Name     : test.cpp
" Author        : skytrails
" Email         : skytrails@163.com
" Create Time   : 2015-09-19 01:10
***************************************************************/

#include "exp.h"
#include <stdio.h>
#include <stdlib.h>
#include "../util/deamon/deamon.h"
#include "../pubclass/process.h"
#include "../pubclass/Trace.h"

int exp_main(int argc, char * argv[]){
    show_info("");
    CExpApp app;
    app.startup();
    
    return 0;
}


CExpApp::CExpApp(){

}

CExpApp::~CExpApp(){

}

int CExpApp::startup(){
    show_info("");
    int ret = init();
    if (0 == ret){
        log_trace(1, "init failed.");
        return 0;
    }
    process();
}

int CExpApp::process(){
    show_info("");
    return 0;
}
