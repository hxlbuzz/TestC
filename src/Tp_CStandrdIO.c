/**
 * @file erl_comm.c
 * @Synopsis  receiving and sending data with
 *	two byte length indicators from/to Erlang.
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.0.1
 * @date 2013-02-19
 */

// Note that stdin and stdout are for buffered input/output
// and should not be used for the communication
#include "Tp_CStandardIO.h"

int read_cmd(byte *buf, int *size) {
	/// may be unsigned short
    unsigned int len = 0;

	/// read 2 byte data from standard input
    if(read_exact(buf, 2) != 2)
        return (-1);
    len = (buf[0] << 8) | buf[1];
	*size = len + 2;
	/// read len bytes data from buf
    return read_exact(buf + 2, len);
}

int write_cmd(byte *buf, int len) {
    byte li = 0;

    li = (len >> 8) & 0xff;
    write_exact(&li, 1);

    li = len & 0xff;
    write_exact(&li, 1);

    return write_exact(buf, len);
}

int read_exact(byte *buf, int len) {
    int i = 0, got = 0;

    do {
        /// standard input
        if((i = read(0, buf + got, len - got)) <= 0)
            return (i);
        got += i;
    } while(got < len);

    return (len);
}

int write_exact(byte *buf, int len) {
    int i = 0, wrote = 0;

    do {
        /// standard output
        if((i = write(1, buf+ wrote, len - wrote)) <= 0)
            return (i);
        wrote += i;
    } while(wrote < len);
    return (len);
}

