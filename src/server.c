#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

#include "content.h"
#include "server.h"

errno_t errno = 0;
static int srv_fd = 0;

int bind_srv()
{
    srv_fd = socket(AF_INET, SOCK_STREAM, 0);

    int port = 3000;
    char *addr = "127.0.0.1";
    struct sockaddr_in srv_addr = {AF_INET, htonl(port), inet_addr(addr)};
    int bind_r = bind(srv_fd, (struct sockaddr *)&srv_addr, sizeof(srv_addr));

    if (bind_r < 0)
    {
        printf("%d %d\n", bind_r, errno);
        return bind_r;
    }

    listen(srv_fd, 10);
    printf("Listening\n");

    return 0;
}

void close_srv()
{
    printf("Stopping\n");
    close(srv_fd);
}

void handle_conn()
{
    int cli_fd = accept(srv_fd, 0, 0);
    printf("\tConnection\n");

    write_statusline(cli_fd);
    write_ct_header(cli_fd);
    write_cl_header(cli_fd);
    write_content(cli_fd);

    close(cli_fd);
}

void serve()
{
    int bind_r = bind_srv();

    if (bind_r == 0)
    {
        while (1)
        {
            handle_conn();
        }
    }

    // TODO: make sure this runs on CTRL+C
    close_srv();
}
