/***************************************************************
" File Name     : SNClient_main
" Author        : skytrails
" Email         : skytrails@163.com
" Create Time   : 2015-10-16 00:37
" Desc          : 
***************************************************************/

#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <iostream>
#include "SNClientProc.h"
#include "../../pubclass/argOptionsMgr.h"
#include "../../pubclass/Trace.h"

using namespace std;

extern "C" int SNClient_main(int argc, char * argv[]){
	show_info("");
    if (argc != 2){
	    log_trace(1, "usage:SNClient 127.0.0.1", 0);
	    exit(0);
    }

    CArgOptionsMgr argMgr(argc, argv);
    const char * c_addr = argMgr.getOptionVal(1);
    log_trace(1, "c_addr:%s", c_addr);
    SNCProc SncProc;
    SncProc.init();
    cout << "SNCProcess" << endl;
    
    SncProc.setAddr(argv[1]);
    SncProc.Process();
    return 0;
}










