/***************************************************************
" File Name     : /home/skytrails/back_trunk/src/pubclass/Trace.h
" Author        : skytrails
" Email         : skytrails@163.com
" Create Time   : 2015-10-15 23:23
***************************************************************/
#define show_info() 
#define log_trace(lev, fmt, arg...) \
{\
    CTrace trace;\
    trace.trace(lev, fmt, ##arg);\
}

class CTrace {
public:
    CTrace(){
      
    }
    ~CTrace(){
    }
    void trace(int lev, const char * fmt, ...);
};
