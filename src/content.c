#include <string.h>
#include <unistd.h>

#include "cmas.h"

void write_statusline(int fd)
{
    const char *sl = "HTTP/1.1 200 OK\r\n";
    write(fd, sl, strlen(sl));
}

void write_ct_header(int fd)
{
    const char *ct = "Content-Type: text/plain; charset=utf-8\r\n";
    write(fd, ct, strlen(ct));
}

void write_cl_header(int fd)
{
    // both responses are 20 chars
    const char *cl = "Content-Length: 20\r\n";
    write(fd, cl, strlen(cl));
}

void write_content(int fd)
{
    char *cnt =
        cmas() ? "\r\nIt's Christmas!!!!\r\n" : "\r\nIt's not Christmas\r\n";

    write(fd, cnt, strlen(cnt));
}
