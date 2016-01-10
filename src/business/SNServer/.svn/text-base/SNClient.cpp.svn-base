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
#include "business/SNServer/SNClientProc.h"

using namespace std;

extern "C" int SNClient_main(int argc, char * argv[]){
    cout<< "fasd" << endl;
    if (argc != 2){
      printf("usage:fault");
      exit(0);
    }
    SNCProc SncProc;
    SncProc.init();
    cout << "SNCProcess" << endl;
    
    SncProc.setAddr(argv[1]);
    SncProc.Process();
    return 0;
}










