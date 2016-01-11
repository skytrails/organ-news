/* Copyright (C)
 * 2016 - skytrails
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */
#include "argOptionsMgr.h"
#include <stdio.h>
#include "Trace.h"

/**
 * @brief
 *
 * @param argc
 * @param argv[]
 */

CArgOptionsMgr::CArgOptionsMgr(int argc, char * argv[]) {
    reset(argc, argv);
}

/**
 * @brief 初始化进程参数
 *
 * @param argc
 * @param argv[]
 */
void CArgOptionsMgr::reset(int argc, char * argv[]) {
    show_info("");
    string tArg("");
    _argc = argc;

    for (int i = 0; i < argc; i++) {
        _argv.push_back(argv[i]);
        tArg += argv[i];
        tArg += " ";
    }

    log_trace(1, "exec : %s", tArg.c_str());
}

/**
 * @brief 通过参数项获取参数值
 *
 * @param opt
 *
 * @return
 */
const char * CArgOptionsMgr::getOptionVal(const char * opt) {
    show_info("");

    if (1) {
        return NULL;
    }
}

/**
 * @brief 通过index获取参数值
 *
 * @param idx
 *
 * @return
 */
const char * CArgOptionsMgr::getOptionVal(int idx) {
    show_info("");

    try {
        if (idx < 0 || idx > _argc) {
            log_trace(1, "idx is overflows!");
            return NULL;
        }

        log_trace(1, "OptionVal[%d]:%s", idx, _argv[idx].c_str());
        return _argv[idx].c_str();

    } catch (...) {
        return NULL;
    }
}

const char * CArgOptionsMgr::OptsProcess() {

}
