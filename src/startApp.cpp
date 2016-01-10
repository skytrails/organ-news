/***************************************************************
" File Name     : startApp.cpp
" Author        : skytrails
" Email         : skytrails@163.com
" Create Time   : 2015-09-16 23:23
***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <errno.h>
#include <string>
#include "./util/deamon/deamon.h"
#include "./pubclass/process.h"
#include "./pubclass/Trace.h"
#define _DEBUG l
using namespace std;
typedef int (*fpfunc)(int argc, char * argv[]);
const char * App_Arr[]={
    "tst",
    "fanyi",
    "skytrails",
    "SNServer",            //
    "startapp.1.0"
};

class CStartApp{
public:
    CStartApp(){};
    ~CStartApp(){};
    int startup(int argc, char * argv[]){
        char * login = getenv("HOME");
        string slib = login;
        slib += "/bin/libBusiness.so";
        void * handle = dlopen(slib.c_str(),RTLD_LAZY);
        if (NULL == handle){
            char * error = dlerror();
            if (error != NULL){
                printf("call dlopen failed,the errcode is %s\n", error);
            }
            cout << "call dlopen failed!" << endl;
        }
        else {
            string _fun = argv[0];
            _fun += "_main";
            fpfunc func = (fpfunc)dlsym(handle,_fun.c_str());
            if (NULL == func){
                cout << "call "<< _fun.c_str() << " @ dlsym failed!" << endl;
            }
            else {
                //cout << "call "<< _fun.c_str() << " begin!";
                func(argc, argv);
            }
        }
    }
};

int main(int argc, char * argv[]){
    CStartApp excApp;
    excApp.startup(argc, argv);
    exit(0);
}


















