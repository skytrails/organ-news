/***************************************************************
" File Name     : src/pubclass/Trace.cpp
" Author        : skytrails
" Email         : skytrails@163.com
" Create Time   : 2015-10-15 23:22
***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "Trace.h"
void CTrace::trace(int lev, const char * fmt, ...){
    char * slev = getenv("LOG_TRACE_LEVEL");
    int ilev = atoi(slev);
    if (ilev > lev ) return ;
    va_list va_ptr;
    va_start(va_ptr, fmt);
    char s[100];
    vsprintf(s, fmt, va_ptr);
    printf(s);
    printf("\n");
    va_end(va_ptr);
}
