/***************************************************************
" File Name     : SNServer_main
" Author        : skytrails
" Email         : skytrails@163.com
" Create Time   : 2015-10-16 00:37
" Desc          : 
***************************************************************/

#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

#include "business/SNServer/SNServerProc.h"

using namespace std;
void sig_action(int signo);

extern "C" int SNService_main(int argc, char * argv[]){
    cout<< "fasd" << endl;
    SNSProc SnsProc;
    signal(SIGCHLD, sig_action);
    SnsProc.init();
    cout << "SNSProcess" << endl;
    SnsProc.SNSProcess();
    return 0;
}

void sig_action(int signo){
  pid_t pid;
  int stat;
  pid = wait(&stat);
  printf("child %d terminated\n", pid);
  return;
}
















