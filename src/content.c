#include <unistd.h>

#include "cmas.h"

void write_statusline(int fd)
{
    write(fd, "HTTP/1.1 200 OK\r\n", 17);
}

void write_ct_header(int fd)
{
    write(fd, "Content-Type: text/html\r\n", 25);
}

void write_cl_header(int fd)
{
    // both responses are 20 chars
    write(fd, "Content-Length: 20\r\n", 20);
}

void write_content(int fd)
{
    write(fd, "\r\n", 2);

    if (cmas())
    {
        write(fd, "It's Christmas!!!!\r\n", 20);
    }

    write(fd, "It's not Christmas\r\n", 20);
}
