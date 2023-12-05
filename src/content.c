#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "content.h"

void write_statusline(int fd)
{
    write(fd, "HTTP/1.0 200 OK\n", 16);
}

void write_ct_header(int fd)
{
    write(fd, "Content-Type: text/html\n", 24);
}

void write_cl_header(int fd)
{
    // both responses are 19 chars
    write(fd, "Content-Length: 19\n", 19);
}

void write_content(int fd)
{
    time_t t = time(NULL);
    struct tm *dt = localtime(&t);

    write(fd, "\n", 1);

    if (dt->tm_mday == 25 && dt->tm_mon == 11)
    {
        write(fd, "It's Christmas!!!!\n", 19);
    }

    write(fd, "It's not Christmas\n", 19);
}
