/**
 * @file erl_comm.h
 * @Synopsis
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.0.1
 * @date 2013-02-19
 */

#ifndef __ERL_COMM_H__
#define __ERL_COMM_H__
#include <unistd.h>
#include "common/Tp_typedef.h"

DECLS_BEGIN
    typedef unsigned char byte;
    int read_cmd(byte *buf, int *size);
    int write_cmd(byte *buf, int len);
    int read_exact(byte *buf, int len);
    int write_exact(byte *buf, int len);
DECLS_END

#endif
