/***************************************************************
" File Name     : /home/skytrails/back_trunk/src/pubclass/Trace.h
" Author        : skytrails
" Email         : skytrails@163.com
" Create Time   : 2015-10-15 23:23
***************************************************************/
#ifndef _TRACE_H_
#define _TRACE_H_
#define show_info(_CLASS) \
/*{*/\
	const char * g_funcname = __FUNCTION__;\
	const char * g_classname = _CLASS;\
	CTrace trace(g_funcname, g_classname);\
/*}*/

#define log_trace(lev, fmt, arg...) \
    trace.trace(lev, fmt, ##arg);

class CTrace {
public:
    CTrace(){
    }
    CTrace(const char * f, const char * c){
	    _funcName = f;
	    _className = c;
    }
    ~CTrace(){
    }
    void trace(int lev, const char * fmt, ...);
private:
    // 函数名与类名
    const char * _funcName;
    const char * _className;
};

#endif
