#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "content.h"
#include "server.h"

static int srv_fd = 0;
static int cli_fd = 0;

int bind_srv()
{
    srv_fd = socket(AF_INET, SOCK_STREAM, 0);

    int port = 3000;
    char *addr = "127.0.0.1";

    struct sockaddr_in srv_addr;
    memset(&srv_addr, 0, sizeof(srv_addr));
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(port);
    inet_pton(AF_INET, addr, &(srv_addr.sin_addr));
    int bind_r = bind(srv_fd, (struct sockaddr *)&srv_addr, sizeof(srv_addr));

    if (bind_r < 0)
    {
        printf("Could not bind\n");
        return bind_r;
    }

    listen(srv_fd, 10);
    printf("Listening\n");

    return 0;
}

void handle_conn()
{
    cli_fd = accept(srv_fd, 0, 0);
    printf("\tConnection\n");

    write_statusline(cli_fd);
    write_ct_header(cli_fd);
    write_cl_header(cli_fd);
    write_content(cli_fd);

    close(cli_fd);
}

void stop_srv()
{
    close(cli_fd);
    close(srv_fd);

    printf("Stopping\n");
    exit(0);
}

void kill_srv(int sig)
{
    printf("Caught %d sig. Wizard was hit for 5hp!\n", sig);
    stop_srv();
}

void serve()
{
    signal(SIGINT, kill_srv);
    signal(SIGTERM, kill_srv);

    int bind_r = bind_srv();

    if (bind_r < 0)
    {
        printf("Could not start server\n");
        stop_srv();
    }

    while (1)
    {
        handle_conn();
    }

    stop_srv();
}
