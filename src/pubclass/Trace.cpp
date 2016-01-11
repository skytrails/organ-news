/***************************************************************
" File Name     : src/pubclass/Trace.cpp
" Author        : skytrails
" Email         : skytrails@163.com
" Create Time   : 2015-10-15 23:22
***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string>
#include <string.h>
#include "Trace.h"
using std::string;
void CTrace::trace(int lev, const char * fmt, ...) {
    char * slev = getenv("LOG_TRACE_LEVEL");
    int ilev;

    if (slev == NULL) {
        printf("CTrace.trace()::warning:LOG_TRACE_LEVEL is not exproted\n");
        ilev = 0;

    } else {
        ilev = atoi(slev);
    }

    if (ilev > lev) {
        return ;
    }

    va_list va_ptr;
    va_start(va_ptr, fmt);
    char s[100];
    vsprintf(s, fmt, va_ptr);

    if (strcmp(_className, "") == 0) {
        sprintf(s, "%s::%s", _funcName, va_ptr);
    } else {
        sprintf(s, "%s.%s::%s", _className, _funcName, va_ptr);
    }

    printf("%s\n", s);
    va_end(va_ptr);
}
