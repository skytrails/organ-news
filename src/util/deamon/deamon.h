#ifndef __DEAMON_H__
#define __DEAMON_H__

#include <iostream>
#include <signal.h>

extern "C" int func();
int z_deamon();
extern "C" void deamonize(const char *cmd);
int set_cloexec(int fd);

#endif
