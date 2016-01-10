/***************************************************************
" File Name     : excApp.cpp
" Author        : skytrails
" Email         : skytrails@163.com
" Create Time   : 2015-09-18 00:30
***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "excApp.h"
#define APP_NAME_LEN
using namespace std;
// add app name
const char* App_Arr[] = {
    "deamon",
    "sky",
    "fanyi"
};

int callApp(int argc, char *argv[]){
    cout << endl;
    const char* fpApp;
    fpApp = App_Arr[0];
    int n = sizeof (App_Arr) / sizeof (const char *);
    for (int i = 0; i < n; ++i){
        if (strcmp(App_Arr[i], argv[0]) == 0){
            break;
        }
        else{
            cout << "can't find " << argv[0] << " app" << endl;
            break;
        }
    }
    return 0;
}
CExcApp::CExcApp(){
    // TODO ADD CODE
}

CExcApp::~CExcApp(){
    // TODO ADD CODE
}

int CExcApp::callApp(int argc, char *argv[]){
    if (strcmp("test", argv[0]) == 0){
        cout << "this is call test app";
    }
    else {
        cout << "this is no that app" << std::endl;
    }
    return 0;
}
